# 🏥 Hospital Patient Management System  
> Developed by **Samarth Kale**, **Abhinaya Gowda**, **Alisha D**, and **Samruddhi Doke**

---

## 📁 Project Structure

This project has **two versions** of the backend system:

### 🔹 1. CLI-Based C Program (`main-cli.c`)
- A terminal-based patient management system written purely in C.
- Allows operations like:
  - Add Patient
  - View Patients
  - Search Patient
  - Delete Patient
- Uses a `do-while` loop and `printf/scanf` for interaction.

### 🔹 2. C + Flask Integration (`main.c` + `app.py`)
- Uses C for core logic (compiled to `libmain.dll`) and Python (Flask) to expose APIs.
- HTML + CSS frontend interacts with the backend via REST.
- Functions:
  - Add Patient
  - View Patient List
  - Search by ID (shows memory address too)
  - Delete Patient
- Includes a visually appealing UI with interactive buttons.

---

## 🛠️ Requirements

Make sure you have the following installed:

### ✅ Software
- GCC (for compiling C code)
- Python 3.10+  
- A code editor (VS Code recommended)

### ✅ Python Packages
```bash
pip install flask flask-cors
```

### ✅ C Compilation
Compile the backend C code (used by Flask) as a DLL:

```bash
gcc -shared -o libmain.dll main.c
```

This will generate `libmain.dll` which Python will load using `ctypes`.

---

## 🚀 How to Run

### 1. 📦 Setup Virtual Environment (Optional but Recommended)

```bash
python -m venv .venv
.\.venv\Scripts\activate
```

### 2. 📥 Install Dependencies

```bash
pip install -r requirements.txt
```

Or manually:

```bash
pip install flask flask-cors
```

### 3. 🔧 Compile the C backend

```bash
gcc -shared -o libmain.dll main.c
```

### 4. 🌐 Run the Flask Server

```bash
python app.py
```

Visit: [http://127.0.0.1:5000](http://127.0.0.1:5000)

---

## 🌈 Frontend Features

- Clean responsive UI using HTML + CSS
- Functional buttons with hover and click effects
- Displays memory address in search
- Full C-to-Python-to-Browser integration

---

## 📝 File Structure (Same Directory Setup)

```
📂 C mini project/
│
├── main.c              # C code (for Flask backend)
├── libmain.dll         # Compiled from main.c
├── main-cli.c          # CLI-based version
├── app.py              # Flask server
├── index.html          # Frontend UI
├── style.css           # CSS styles
├── requirements.txt    # Python package list
├── README.md           # You're reading this!
```

---

## 👨‍💻 Developers
- **Samarth Kale**
- **Abhinaya Gowda**
- **Alisha D**
- **Samruddhi Doke**
