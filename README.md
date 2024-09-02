# Humidity Sensor Arduino Project 🌡️

Welcome to the Humidity Sensor Arduino Project! This project involves creating a digital humidity sensor using analog components, primarily a capacitor from a DHT11 sensor, and interfacing it with an Arduino board. The setup allows you to compare the performance of a custom-made sensor with the standard DHT11 sensor.

## Project Overview 📊

### Hardware Components 🛠️

- **Arduino Board**: Interfaces with both the capacitor and the DHT11 sensor.
- **Capacitor**: Acts as a part of the custom humidity sensor.
- **DHT11 Sensor**: A standard digital sensor for humidity and temperature.

### Software Components 💻

1. **Arduino Code**:
   - Reads data from both the capacitor and the DHT11 sensor.
   - Charges and discharges the capacitor cyclically to measure capacitance.
   - Converts capacitance to numerical values for humidity measurement.
   - Includes a watchdog timer to reset the board and prevent overloading.

2. **Python Code**:
   - Reads data from the Arduino via serial communication.
   - Calibrates capacitance values and converts them to humidity percentages.
   - Stores data in CSV and JSON files for further use.
   - Synchronizes JSON data with `app.py` for web visualization.

3. **Web Interface**:
   - **Flask Application**: Uses the Flask library to connect to an HTML page.
   - **HTML Page**: Visualizes data from the sensors and updates regularly.

## Hardware Setup 📐

<p align="center">
    <img src="https://github.com/user-attachments/assets/5086a559-b765-4a82-80e5-2f0851b851a4" alt="Hardware Setup" height="400"/>
</p>
<p align="center"><em>Figure 1: Hardware Setup - Arduino board, capacitor connected (TinkerCAD Simulation)
https://www.tinkercad.com/things/dr2QzzeNIsl?sharecode=KYGpsa-w2-o5Wj-UnMkk2HqtVg5c03bUycDkxsM94os</em></p>

## Software Architecture 🖥️

<p align="center">
    <img src="https://github.com/user-attachments/assets/0d41b284-9c0e-4334-aeef-f36066d1e462" alt="Circuit Diagram" height="400"/>
</p>
<p align="center"><em>Figure 2: Software Architecture - Integration of Arduino, Python, and web interface</em></p>

## Web Interface Functionality 🌐

<p align="center">
    <img src="https://github.com/user-attachments/assets/6dc1a38d-12cc-41d2-b857-801ecb290c5b" alt="Web Interface Functionality" height="400"/>
</p>
<p align="center"><em>Figure 3: Web Interface Functionality - Data visualization and real-time updates</em></p>

## Python Code Functionality 🐍

<p align="center">
    <img src="https://github.com/user-attachments/assets/e83e3047-3f5c-4148-99fe-b1e3402c0e92" alt="Python Code Functionality" height="400"/>
</p>
<p align="center"><em>Figure 4: Python Code Flow - Data reading, calibration, and storage</em></p>

## Components 📏🔬

| DHT11 Sensor | Capacitor Component |
|--------------|----------------------|
| <img src="https://github.com/user-attachments/assets/fb76e997-f066-4d98-b16e-8645b2882833" alt="DHT11 Sensor" height="200"/> | <img src="https://github.com/user-attachments/assets/a9dae5d5-da76-422e-98db-f3c1bf712196" alt="Capacitor" height="200"/> |

<p align="center"><em>Figure 5: DHT11 Sensor and Capacitor Component used for Humidity Measurement</em></p>

<p align="center">
    <img src="https://github.com/user-attachments/assets/2f567a5e-2e30-44bc-8500-35cfd9e5d149" alt="Capacitor_Charge-Discharge" height="400"/>
</p>
<p align="center"><em>Figure 6: Capacitor Charge-Discharge Cycle for Humidity Measurement</em></p>

<p align="center">
    <img src="https://github.com/user-attachments/assets/6cc8c13f-bb5b-4141-9b0c-ebad6957710d" alt="Value_DHTvsCapacitor" height="400"/>
</p>
<p align="center"><em>Figure 7: Comparison of Humidity Values between DHT11 Sensor and Capacitor</em></p>

## Conclusion 🎯

This project effectively demonstrates the integration of analog and digital components to create a functional humidity sensor system. The combination of Arduino, Python, and web technologies provides a comprehensive solution for environmental monitoring.

Feel free to explore the project and contribute to its development!
