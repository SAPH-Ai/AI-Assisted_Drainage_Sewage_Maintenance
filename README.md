# 🤖 AI-Assisted Drainage & Sewage Maintenance System

![Project Status](https://img.shields.io/badge/Status-Active-brightgreen)
![Platform](https://img.shields.io/badge/Platform-Arduino%20%7C%20Python-blue)
![License](https://img.shields.io/badge/License-MIT-orange)


## 📋 Table of Contents
- [About the Project](#-about-the-project)
- [The Robots](#-the-robots)
  - [1. Surface Drainage Bot (4-Wheeled)](#1-surface-drainage-bot)
  - [2. Sewage Pipeline Bot (6-Wheeled)](#2-sewage-pipeline-bot)
- [Key Features](#-key-features)
- [Tech Stack](#-tech-stack)
- [Hardware & Pin Mapping](#-hardware--pin-mapping)
- [Installation](#-installation)
- [Team](#-team)

---

## 📖 About the Project

Urban areas in developing countries often face severe waterlogging and health hazards due to clogged drainage systems. Manual cleaning is dangerous, exposing workers to toxic gases like Methane ($CH_4$) and hazardous waste.

**The SAPHAI Project** utilizes AI and robotics to autonomously detect blockages, identify toxic gases, and clean drainage systems without risking human lives. Our system consists of two specialized robots driven by Computer Vision and microcontroller logic.

---

## 🤖 The Robots

### 1. Surface Drainage Bot
**Design:** 4-Wheeled Rover  
**Mission:** Open/Flat drain maintenance.  
**Capabilities:** - Navigates surface drains.
- Uses a **6-DOF Robotic Arm** to physically pick up solid waste (bottles, debris).
- Deploys a **High-Pressure Water Jet** to clear sludge and light obstructions.

### 2. Sewage Pipeline Bot
**Design:** 6-Wheeled Crawler  
**Mission:** Deep pipeline inspection and chemical safety.  
**Capabilities:** - Crawls inside narrow sewage pipes.
- **Gas Detection:** Monitors Methane and Ammonia levels.
- **Chemical Mitigation:** Automatically sprays neutralizing chemicals (NaOH/NaClO) if dangerous gas is detected.
- **Water Quality Analysis:** Measures turbidity to distinguish between clean and polluted water.

---

## ✨ Key Features

* **👁️ AI Vision:** Uses OpenCV to identify specific trash types (Plastic bottles, medical waste, organic debris).
* **⚠️ Hazard Mitigation:** Automatic pump activation when explosive gas levels exceed 50%.
* **🦠 Sanitization:** Integrated UV lights and chemical sprays to disinfect contaminated zones.
* **🌚 Dark Navigation:** LDR-controlled floodlights for operating in pitch-black sewers.
* **📊 Real-Time Monitoring:** Live telemetry of Humidity, Temperature, and Air Quality displayed on an onboard LCD.

---

## 🛠 Tech Stack

### Software
* **Brain:** Python (OpenCV, TensorFlow)
* **Body:** C++ (Arduino IDE)
* **Communication:** Serial / Bluetooth (HC-05)

### Hardware Components
* **Microcontrollers:** Arduino Mega 2560 (Main), Arduino Uno (Sensor Node)
* **Drivers:** L298N Motor Driver
* **Sensors:** MQ-135 (Gas), DHT11 (Temp/Hum), Ultrasonic (Distance), Turbidity Sensor, LDR
* **Actuators:** High-Torque DC Motors, Servo Motors (MG996R/SG90), 12V Water Pumps

---

## 🔌 Hardware & Pin Mapping

### Robot 1: Drainage Bot (Mega 2560)
| Component | Pin | Function |
| :--- | :--- | :--- |
| **L Motor** | D22, D23 | Drive Left Wheels |
| **R Motor** | D24, D25 | Drive Right Wheels |
| **Arm Base** | D2 | Robotic Arm Rotation |
| **Arm Grip** | D7 | Open/Close Gripper |
| **Water Jet** | D10 | High-Pressure Cleaning |
| **Ultrasonic**| D11/D12 | Obstacle Avoidance |

### Robot 2: Sewage Bot (Mega 2560)
| Component | Pin | Function |
| :--- | :--- | :--- |
| **6WD Drive** | D7-D10 | All-Wheel Drive |
| **Gas Sensor**| A0 | MQ-135 Reading |
| **Turbidity** | A1 | Water Quality Reading |
| **Chem Pump** | D3 | Spray Chemical |
| **UV Light** | D4 | Sanitization LED |

---

## 🚀 Installation

1.  **Clone the Repo**
    ```bash
    git clone [https://github.com/yourusername/ai-drainage-bot.git](https://github.com/yourusername/ai-drainage-bot.git)
    ```
2.  **Upload Firmware**
    * Open `Drainage_Bot.ino` or `Sewage_Bot.ino` in Arduino IDE.
    * Select the correct board (Arduino Mega 2560) and Port.
    * Install required libraries: `LiquidCrystal_I2C`, `DHT`, `Servo`.
    * Click **Upload**.
3.  **Run AI Script (Optional Host)**
    * Connect the camera to your PC/Raspberry Pi.
    * Run the Python detection script:
    ```bash
    python detect_and_command.py
    ```

---

## 👥 Team

* **Abrar Abir** - *Leader & Mechanical Design*
* **Emtenan Kabir** - *Researcher & Software Integration*
* **Institute:** Dhaka Residential Model College

---

*Project developed for the National Science Fest 2024.*
