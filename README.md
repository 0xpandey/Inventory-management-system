# Inventory Management System (C++)

## 📌 Overview
This project is a console-based Inventory Management System developed in C++ using SQLite for persistent data storage.  
It is designed using a layered architecture to separate concerns between presentation, business logic, and data access.

The goal of this project is to demonstrate real-world C++ application development practices, including modular design, database integration, and clean architecture.

---

## Features

- Add new products with category and price
- Track stock quantity with threshold alerts
- Buy and sell stock with validation
- Automatic transaction logging
- Inventory report
- Low stock alert report
- Sales summary report
- Transaction history
- SQLite-based persistent storage


## Architecture

The project follows a layered architecture:
- Models: Data structures (Product, Stock, Transaction)
- Repository Layer: Handles all database operations (SQLite)
- Service Layer: Business logic (Inventory & Reports)
- Main/Menu Layer: User interaction and navigation


---

## 🛠 Tech Stack
- **Language:** C++17  
- **Database:** SQLite  
- **Build System:** CMake  
- **Version Control:** Git & GitHub  

---

## 📂 Project Status
## Folder Structure

Inventory-management-system/
│
├── src/
│   ├── database/        # Database connection and initialization
│   ├── models/          # Entity models
│   ├── repository/      # Database access layer
│   ├── services/        # Business logic and reports
│   └── main.cpp         # Menu-driven application
│
├── data/
│   └── inventory.db     # SQLite database file
│
├── CMakeLists.txt
├── README.md
└── build/

---

## 📄 Documentation
Detailed technical documentation is available in the `docs/` directory.

---

## 👤 Author
Om Pandey

