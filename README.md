<div align="center">

# 🛒 S&M Online Shopping Cart

A console-based online shopping system built in **C++** for the Programming Fundamentals course — Semester 02.

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Console](https://img.shields.io/badge/Console-App-black?style=for-the-badge)
![Semester](https://img.shields.io/badge/Semester-2-blue?style=for-the-badge)

</div>

---

## 📋 About

A terminal-based shopping cart system with two separate portals — Admin and User. The system handles product management, user registration, cart operations, order placement, and order dispatching, with data stored and read from CSV files.

> 📌 This was the **Final Project** for the subject **Programming Fundamentals** — Semester 02.

**Team Members:**
| Name | ID |
|------|----|
| Sharjeel | L1F24BSCS0506 |
| Moeez | L1F24BSCS0541 |

---

## ⚙️ Features

**🔐 Admin Portal**
- Secure login with password masking and lockout after 3 failed attempts
- Add, edit, delete, and view all products
- Filter products by category
- View low stock alerts (quantity < 10)
- View all, pending, and completed orders
- Dispatch orders and auto-update status with current date

**👤 User Portal**
- Register with username and strong password validation
- Secure login with masked password input
- Browse all available products
- Add items to cart with quantity checking against stock
- View, edit, or clear cart
- Place orders with phone and address details
- 10% discount auto-applied on orders over 7 days rental
- Cancel placed orders
- Track order dispatch status

**📁 File-Based Storage**
- All data persisted across sessions via CSV files
- `Products.csv` , `Users.csv` , `Carts.csv` , `Orders.csv` , `Order Details.csv`

---

## 🚀 How to Run

### Option 1 — Any C++ Compiler
```bash
g++ main.cpp admin.cpp user.cpp -o shopping-cart
./shopping-cart
```

### Option 2 — Visual Studio

1. Create a new **Empty C++ Project**
2. Add all `.cpp` source files to the project
3. Press **`Ctrl+F5`** to build and run

> No external libraries required — standard C++ only. Make sure all CSV files are in the same directory as the executable.

---

## 🗂️ Project Structure
```
projects/
└── s&m-shopping-cart/
    ├── !project.zip          # Complete Visual Studio project
    ├── main.cpp              # Entry point — main menu
    ├── admin.cpp             # Admin portal logic
    ├── user.cpp              # User portal logic
    ├── Products.csv          # Product data
    ├── Users.csv             # Registered users
    ├── Carts.csv             # Active carts
    ├── Orders.csv            # Order summaries
    ├── Order Details.csv     # Per-order product details
    └── README.md
```

---

## 🔑 Default Admin Credentials

| Field | Value |
|-------|-------|
| Username | `admin` |
| Password | `12345678` |

---

## 📄 License

This project is open source and available under the [MIT License](https://github.com/Sharjeel7911/projects/blob/main/LICENSE).

---

<div align="center">
Made with ❤️ and C++ <br>
</div>