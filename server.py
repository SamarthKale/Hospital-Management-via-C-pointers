import ctypes
import json
from flask import Flask, request, jsonify, render_template
from flask_socketio import SocketIO
from flask_cors import CORS

# --- Initialize the App, CORS, and SocketIO ---
app = Flask(__name__)
CORS(app)
socketio = SocketIO(app, cors_allowed_origins="*")

# --- Load the C Library and Define Functions ---
try:
    lib = ctypes.CDLL('./libqueue.dll')

    # Define function signatures from the C code
    lib.enqueue_patient.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
    lib.enqueue_patient.restype = ctypes.c_int

    lib.dequeue_patient.restype = ctypes.c_int

    lib.update_patient_status.argtypes = [ctypes.c_int, ctypes.c_char_p]
    lib.update_patient_status.restype = ctypes.c_int

    lib.get_queue_as_json.argtypes = [ctypes.c_char_p, ctypes.c_int]
    lib.get_queue_as_json.restype = None
    
    lib.get_address_log_json.argtypes = [ctypes.c_char_p, ctypes.c_int]
    lib.get_address_log_json.restype = None

except Exception as e:
    print(f"FATAL: Could not load C library 'libqueue.dll'. Error: {e}")
    lib = None

# --- Helper Function to Broadcast All Updates ---
def broadcast_full_update():
    """Gets both queue and log data from C and sends it to all clients."""
    if not lib: return
    
    # 1. Broadcast queue data
    queue_buffer = ctypes.create_string_buffer(4096)
    lib.get_queue_as_json(queue_buffer, 4096)
    queue_data = json.loads(queue_buffer.value.decode('utf-8'))
    socketio.emit('queue_update', queue_data)
    
    # 2. Broadcast address log data
    log_buffer = ctypes.create_string_buffer(8192)
    lib.get_address_log_json(log_buffer, 8192)
    log_data = json.loads(log_buffer.value.decode('utf-8'))
    socketio.emit('address_update', log_data)
    
    print("Broadcasted full update (queue and address log).")

# --- API Routes ---
@app.route('/')
def index():
    """Serves the main index.html file."""
    return render_template('index.html')

@app.route('/api/queue/enqueue', methods=['POST'])
def api_enqueue():
    data = request.get_json()
    name = data.get('name').encode('utf-8')
    service = data.get('service_type').encode('utf-8')
    new_id = lib.enqueue_patient(name, service)
    broadcast_full_update()
    return jsonify({"message": "Patient added", "id": new_id})

@app.route('/api/queue/dequeue', methods=['POST'])
def api_dequeue():
    called_id = lib.dequeue_patient()
    broadcast_full_update()
    if called_id != -1:
        return jsonify({"message": "Called next patient", "id": called_id})
    return jsonify({"message": "Queue is empty"}), 404

@app.route('/api/queue/update_status', methods=['POST'])
def api_update_status():
    data = request.get_json()
    patient_id = data.get('id')
    status = data.get('status').encode('utf-8')
    lib.update_patient_status(patient_id, status)
    broadcast_full_update()
    return jsonify({"message": f"Patient {patient_id} status updated"})

@app.route('/api/queue/current', methods=['GET'])
def api_get_current():
    buffer = ctypes.create_string_buffer(4096)
    lib.get_queue_as_json(buffer, 4096)
    return jsonify(json.loads(buffer.value.decode('utf-8')))

# --- Socket.IO Event Handlers ---
@socketio.on('connect')
def handle_connect():
    print('Client connected')
    broadcast_full_update()

# --- Run the Server ---
if __name__ == '__main__':
    if not lib:
        print("Cannot start server because C library failed to load.")
    else:
        print("Starting server on http://127.0.0.1:5000")
        socketio.run(app, port=5000)