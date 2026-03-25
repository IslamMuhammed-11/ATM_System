# ATM_System
🏧 ATM System (C++)

This is a simple console-based ATM system built using C++.
The main goal of this project was to practice working with files, organizing code, and applying a functional programming style.

📌 Overview

The system simulates basic ATM operations where a user can log in using an account number and PIN, then perform transactions like withdrawing, depositing, and checking balance.

🚀 Features
🔐 Login system (Account Number + PIN)
⚡ Quick Withdraw (fixed amounts)
💵 Normal Withdraw (custom amount)
💰 Deposit money
📊 Check account balance
🔄 Logout and re-login
🧠 What I focused on
Using functional programming instead of OOP
Separating logic from UI (menus vs operations)
Working with files using fstream
Storing and retrieving data from a text file
Building my own split function to parse strings
Manually converting between struct and string (serialization)
🗂️ Data Storage

All data is stored in a plain text file:

Clients.txt

Each record is saved like this:
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance

Example:
A123#//#1234#//#Eslam Mohammed#//#01012345678#//#5000
⚙️ How it works
When the program starts, the user logs in using account number and PIN
Data is loaded from the file into memory
Any transaction (deposit / withdraw) updates the data
Changes are saved back to the file immediately
The logged-in user is stored in a global variable during the session
▶️ How to run
Clone the repository
Open the project using Visual Studio (or any C++ compiler)
Run the program
📌 Notes
This project is for learning purposes
No database is used, only plain text file storage
No encryption for PIN codes (just for simplicity)
🔧 Possible Improvements
Add encryption for PIN codes
Convert the project to OOP
Support multiple users with roles
