# Console-Based Database Management System (C++ with SQL)

## 📌 Description
This project is a **console-based C++ application** that interacts with an **SQL database** to perform basic **CRUD operations** (Create, Read, Update, Delete). It allows users to manage a simple database of user records efficiently.

## 🔹 Features
- **Database Integration**: Supports **SQL**.
- **Basic CRUD Operations**:
  1. **Insert** a new record.
  2. **Update** an existing record.
  3. **Delete** a record by **ID**.
  4. **Display** all records.
- **Console-based User Interface**: Simple and easy-to-use text-based menu.

## 🛠️ Requirements
- **C++** (Standard C++17 or later)
- **SQL Database**
- **CMake (Optional)** (for easier project compilation)

## 📜 Database Schema
The application manages a **Users** table with the following structure:
```sql
CREATE TABLE Users (
    ID INTEGER PRIMARY KEY AUTO_INCREMENT,
    Name VARCHAR(255) NOT NULL,
    Age INTEGER NOT NULL
);
```




