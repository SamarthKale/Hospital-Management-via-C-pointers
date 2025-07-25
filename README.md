# 🏥 Hospital Management System (CLI Version)

A simple **terminal-based** hospital patient record management system written in C.

> Developed by **Samarth Kale**, **Abhinaya Gowda**, **Alisha D**, and **Samruddhi Doke**

---

## 📌 Features

- ➕ Add new patient
- 📋 View all patients
- 🔍 Search patient by ID
- ❌ Delete patient record
- 🧠 Displays memory address of each patient node (for debugging/educational purposes)
- ✅ All input is validated with clear prompts and error handling
- 🎨 Uses emojis and basic styling to make the terminal output more friendly

---

## 🛠️ Requirements

- A C compiler like **MinGW-w64** (recommended for Windows)
- No other external libraries needed

### 🧩 Install MinGW-w64 on Windows:

1. Download from: [https://www.mingw-w64.org/downloads/](https://www.mingw-w64.org/downloads/)
2. During installation:
   - Architecture: `x86_64`
   - Threads: `posix`
   - Exception: `seh`
3. Add the **bin** folder (e.g., `C:\Program Files\mingw-w64\...\bin`) to your **system PATH**
4. Verify installation with:
   ```bash
   gcc --version
   ```

---

## 🧪 How to Compile and Run

### On Windows using GCC (MinGW-w64):

```bash
gcc main.c
a.exe
```

Or to name the output:

```bash
gcc main.c -o hospital.exe
hospital.exe
```

> Replace `main.c` with your actual filename if it's different.

---

## 🧠 How It Works

- Patients are stored in a **singly linked list** (`struct Patient`)
- Each node contains:
  - ID
  - Name
  - Age
  - Disease
  - Pointer to next patient
- Functions handle adding, deleting, searching, and viewing the list
- Memory addresses are printed for each patient to help understand pointers

---

## 📷 Screenshot (Sample Output)

```
==================================================================
         🏥  HOSPITAL MANAGEMENT SYSTEM - MAIN MENU  🏥         
==================================================================
👋 Welcome! Please choose one of the following options:
------------------------------------------------------------------
 [1] ➕ Add New Patient         - Register a new patient record
 [2] 📋 View All Patients       - Display the full patient list
 [3] 🔍 Search for a Patient    - Lookup a patient by ID
 [4] ❌ Delete a Patient Record - Remove a patient from the system
 [5] 🚪 Exit the System         - Close the application
==================================================================
🖊️  Enter your choice (1 - 5): 
```

---

## 👨‍💻 Developers

- **Samarth Kale**
- **Abhinaya Gowda**
- **Alisha D**
- **Samruddhi Doke**

---

## 🧹 Cleanup

The program automatically frees all allocated memory before exiting.  
No memory leaks!

---

## 📂 File Structure

```
main.c          # Contains the complete C code
README.md       # This file
```

---

## 📌 Note

This is a **standalone C project** meant to demonstrate:
- Data structures (Linked List)
- Memory management in C
- Console I/O and control
- Most importantly use of Pointers 

There’s no frontend, database, or web backend in this version. To visit that version change the branch to Frontend+C
