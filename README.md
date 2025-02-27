# IoT-based Campus Water Level Monitoring & Management System

## Overview

This project is an IoT-based water level monitoring and management system designed to efficiently monitor water tank levels across a campus. The system uses IoT devices to sense water levels, track truck locations via GPS, and transmit this data to the cloud for further processing and monitoring. It provides real-time updates and alerts to users, making it an effective solution for campus water management.

---

## Project Features

- **Real-Time Water Level Monitoring**: Continuously tracks water tank levels using ultrasonic water level sensors (HC-SR04).
- **GPS Tracking**: Uses GPS modules (NEO-6M) to monitor truck locations for efficient water distribution.
- **Cloud Integration**: Data is transmitted to InfluxDB Cloud via HTTP, where it is stored and analyzed.
- **Grafana Dashboard**: Real-time visualization of water levels and truck locations.
- **Solar-Powered**: The system is powered by solar panels, making it energy-efficient and sustainable.
- **Notifications**: Push notifications for low water levels or abnormal conditions to alert users.

---

## System Architecture

The system is designed with a layered architecture to ensure modularity, scalability, and efficient communication. The key components of the system are:

1. **Sensor Layer**:
   - Water Level Sensors (HC-SR04) to detect water levels.
   - GPS Modules (NEO-6M) for truck location tracking.

2. **Communication Layer**:
   - ESP32 Microcontroller for local data processing and communication.
   - HTTP Protocol for cloud data transmission to InfluxDB Cloud.

3. **Cloud Layer**:
   - Data stored in **InfluxDB Cloud**.
   - Real-time analytics using **Grafana** for monitoring.

4. **Power Management**:
   - **Solar panel (6V/3W)** for power generation.
   - **TP4056 Battery Management Module** for charging.
   - **ICR18650-1S 3.7V Battery** for energy storage and continuous operation.

---

## Components Used

- **ESP32 Microcontroller**: Manages sensors, processes data, and transmits it to the cloud.
- **Water Level Sensor (HC-SR04)**: Measures the water tank level.
- **GPS Module (NEO-6M)**: Tracks truck locations for water delivery.
- **HTTP Communication**: Sends data to InfluxDB Cloud.
- **InfluxDB Cloud**: Stores sensor data for analysis and visualization.
- **Grafana**: Visualizes water level and truck location data in real-time.
- **Solar Panel (6V/3W) & TP4056**: Powers the system sustainably.
- **ICR18650-1S 3.7V Battery**: Provides backup power.

---

## Installation & Setup

### Prerequisites
- Arduino IDE or PlatformIO for ESP32 programming.
- InfluxDB Cloud account for data storage.
- Grafana setup for real-time visualization.
- Solar panel and battery setup for power.

### Steps

1. **Hardware Setup**:
   - Connect the water level sensor (HC-SR04) and GPS module (NEO-6M) to the ESP32.
   - Set up HTTP communication to send data to InfluxDB Cloud.
   - Power the system using a **6V/3W solar panel, TP4056, and ICR18650-1S battery**.

2. **Software Setup**:
   - Install the required libraries in Arduino IDE (e.g., `WiFi`, `HTTPClient`).
   - Upload the code to the ESP32 to read sensor data and send it to the cloud.
   - Configure InfluxDB Cloud for data storage.
   - Set up **Grafana** and connect it to InfluxDB Cloud for visualization.

3. **Cloud & Grafana Integration**:
   - Configure **InfluxDB Cloud** to store sensor data.
   - Set up **Grafana** to visualize water level and GPS data.
   - Enable alerts for low water levels using **Grafana notifications**.

---

## Future Enhancements

- **Mobile App Development**: Develop a mobile app using Flutter or React Native to display real-time water tank levels, truck locations, and send alerts.
- **Advanced Analytics**: Use AI/ML to predict water usage patterns and optimize water distribution.
- **Multi-Tank Support**: Extend the system to support multiple water tanks across the campus.
- **Energy Management**: Implement energy-saving modes for more efficient power usage.
- **Weather Integration**: Integrate weather data to predict water usage needs based on external factors like rainfall.

---

This project ensures efficient water management using IoT, real-time monitoring, and sustainable energy solutions, making it an essential tool for campus-wide water level tracking and optimization.

