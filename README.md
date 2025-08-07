# Address_Book_Project-# 📇 Address Book - Console Based Application in C

This is a simple **console-based Address Book application** developed in **C** as part of the **Embedded Systems internship** at *Emertxe Information Technologies*. The project allows users to manage their contacts by adding, viewing, editing, searching, and deleting records with persistent file storage.

---

## 📌 Features

- Add new contacts (Name, Phone, Email, etc.)
- View all contacts in a readable tabular format
- Search for a contact by name or phone number
- Edit existing contact details
- Delete contacts
- Data persistence using `.txt` or `.csv` files
- Simple, menu-driven interface in the console

---

## 🧰 Technologies Used

- **Language:** C  
- **Platform:** Linux Console  
- **Compiler:** GCC  
- **Concepts:** Structures, File I/O, Modular Programming  
- **Storage:** Text-based file handling  

---

## 📂 Project Structure

├── main.c # Entry point, handles menu
├── contact.c/h # Contact data and operations
├── file.c/h # File read/write functions
├── populate.c/h # Load data into memory
├── declaration.c # Global functions or variable declarations
├── contacts.txt # Persistent data storage

---

## 🚀 How to Run

### 🔧 Compile:
gcc main.c contact.c file.c populate.c declaration.c -o addressbook
### ▶️ Execute:
./addressbook
Ensure contacts.txt or contacts.csv exists in the same directory or will be created on first run.

---

## 📖 Learning Outcomes
- Hands-on experience with structured and modular C programming
- Real-time implementation of file handling in C
- Debugging and building real-time console applications

