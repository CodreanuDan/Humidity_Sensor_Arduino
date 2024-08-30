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

## Hardware Setup 🖥️

![Hardware Setup](https://github.com/user-attachments/assets/5086a559-b765-4a82-80e5-2f0851b851a4)

## Circuit Diagram 📐

![Circuit Diagram](https://github.com/user-attachments/assets/0d41b284-9c0e-4334-aeef-f36066d1e462)

## Web Interface Functionality 🌐

![Web Interface Functionality](https://github.com/user-attachments/assets/6dc1a38d-12cc-41d2-b857-801ecb290c5b)

## Python Code Functionality 🐍

![Python Code Functionality](https://github.com/user-attachments/assets/e83e3047-3f5c-4148-99fe-b1e3402c0e92)

## Components 📏🔬

| DHT11 Sensor | Capacitor Component |
|--------------|----------------------|
| ![DHT11 Sensor](https://github.com/user-attachments/assets/fb76e997-f066-4d98-b16e-8645b2882833) | ![Capacitor](https://github.com/user-attachments/assets/a9dae5d5-da76-422e-98db-f3c1bf712196) |


## Conclusion 🎯

This project effectively demonstrates the integration of analog and digital components to create a functional humidity sensor system. The combination of Arduino, Python, and web technologies provides a comprehensive solution for environmental monitoring.

Feel free to explore the project and contribute to its development!

