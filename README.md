# 🥤 Vending Machine Using PIC Microcontroller

This project is a simple **vending machine system** controlled by a **PIC microcontroller**, programmed in **C language**. It accepts **two types of coins**, allows users to select between **three different products**, and performs all required operations to simulate a real vending machine.

---

## ⚙️ System Overview

- **Microcontroller:** PIC (e.g., PIC16F877A)
- **Language:** C (compiled with MPLAB X and XC8)
- **Accepted Coins:** Two types (e.g., 500 and 1000 units)
- **Products:** Three types (e.g., Water, Soda, Juice)
- **User Inputs:** Coin inputs and product selection buttons
- **Outputs:** Product dispense signal, credit tracking, optional LEDs or display

---

## 🧩 Components Used

- PIC Microcontroller (e.g., PIC16F877A)
- Push Buttons (for coin and product inputs)
- LEDs or 7-Segment Display (optional feedback)
- Output actuators (e.g., motors, relays for product dispensing)
- Breadboard or PCB
- Power Supply (e.g., 5V regulated)
- Resistors, capacitors, and other passive components

---

## 🧠 Functional Description

1. The user inserts coins.
2. The microcontroller adds the value of the coin to the internal credit.
3. The user selects a product using one of the three buttons.
4. The system checks if the inserted credit is enough for the selected product.
5. If enough credit is available:
   - The product is dispensed.
   - The credit is updated.
6. If the credit is insufficient:
   - A warning can be shown (e.g., LED or message on display).
