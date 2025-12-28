# 🤖 SAPHAI Bot Firmware Repository

![Arduino](https://img.shields.io/badge/Platform-Arduino_Mega_2560-teal)
![Language](https://img.shields.io/badge/Code-C++-blue)
![Status](https://img.shields.io/badge/Build-Passing-brightgreen)

This repository contains the embedded control software for the **SAPHAI** project. The system operates on two distinct firmware sketches tailored for specific drainage environments.

---

## 📂 Code Structure

### 1. `Drainage_Bot_Mega.ino` (Surface Robot)
**Target Hardware:** 4-Wheeled Rover w/ Robotic Arm
**Core Logic:**
* **Autonomous Obstacle Avoidance:** Uses Ultrasonic sensors to detect solid blockages (<30cm).
* **Robotic Arm Control:** 6-DOF inverse kinematics logic to execute `GRAB` and `DROP` sequences for solid waste.
* **Water Jet Activation:** Triggers high-pressure pumps to clear sludge when the arm is engaged.
* **Command Parsing:** Listens for `F`, `B`, `L`, `R` navigation commands via Bluetooth or AI Serial link.

### 2. `Sewage_Bot_Mega.ino` (Pipeline Robot)
**Target Hardware:** 6-Wheeled Crawler w/ Chemical Labs
**Core Logic:**
* **Gas Safety Protocol:** Polling loop for MQ-135 sensor; triggers chemical neutralization pump if $CH_4$ > 50%.
* **Water Quality Indexing:** Maps analog Turbidity values to determine water cleanliness; activates UV sanitation for high turbidity.
* **Environment Telemetry:** Reads DHT11 (Temp/Hum) and updates the I2C LCD in real-time.
* **Dark Mode:** Auto-activates high-power LEDs when LDR detects low light levels.

---

## 📦 Required Libraries
Ensure these libraries are installed in your Arduino IDE before compiling:

| Library | Usage | Install via |
| :--- | :--- | :--- |
| **`Servo.h`** | Robotic Arm Control | Built-in |
| **`LiquidCrystal_I2C.h`** | LCD Display Control | Library Manager |
| **`DHT.h`** | Temperature/Humidity | Library Manager |
| **`Wire.h`** | I2C Communication | Built-in |

---

## 🔌 Pin Map Quick Reference

#### **Drainage Bot (Robot 1)**
```cpp
// Motor Driver (L298N)
Left_Motors:  Pins 22, 23 (PWM 8)
Right_Motors: Pins 24, 25 (PWM 9)

// Actuators
Water_Pump:   Pin 10
Arm_Servos:   Pins 2-7
