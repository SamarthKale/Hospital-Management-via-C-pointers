from flask import Flask, request, jsonify, send_file
import ctypes

app = Flask(_name_)

# Load the DLL
lib = ctypes.CDLL('./libmain.dll')

# Set function signatures
lib.add_patient.argtypes = [ctypes.c_int, ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]
lib.add_patient.restype = None

lib.get_patient_info.argtypes = [ctypes.c_int, ctypes.c_char_p, ctypes.POINTER(ctypes.c_int), ctypes.c_char_p]
lib.get_patient_info.restype = ctypes.c_int

@app.route('/')
def home():
    return send_file('index.html')  # Load from same directory

@app.route('/add_patient', methods=['POST'])
def add_patient():
    data = request.get_json()
    id = data['id']
    name = data['name'].encode()
    age = data['age']
    disease = data['disease'].encode()

    lib.add_patient(id, name, age, disease)
    return jsonify({'status': 'Patient added successfully'})

@app.route('/search_patient/<int:pid>', methods=['GET'])
def search_patient(pid):
    name = ctypes.create_string_buffer(100)
    disease = ctypes.create_string_buffer(100)
    age = ctypes.c_int()

    found = lib.get_patient_info(pid, name, ctypes.byref(age), disease)
    if not found:
        return jsonify({'error': 'Patient not found'}), 404

    # Simulate memory address by getting buffer address (not real C pointer)
    address = hex(ctypes.addressof(name))  # or disease or create a fake one

    return jsonify({
        'id': pid,
        'name': name.value.decode(),
        'age': age.value,
        'disease': disease.value.decode(),
        'memory_address': address
    })


if _name_ == '_main_':
    app.run(debug=True)
