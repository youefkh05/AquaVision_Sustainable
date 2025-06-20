# Embedded Systems Project (ELC2080)


![TEAM Logo Main](Team_Graphics/Export%20logo.png)

>[!IMPORTANT]
> This project is done as part of the Embedded Systems course [ELC2080] taught to second year Electronics and Elecrtic Communication Engineering Students at Cairo University Under the Supervision of Dr. Mohamed Riad.

### **[Dashboard Link](https://amirsameh1.github.io/test/)** To monitor project Data in real-time

## Brief Description

The system employs a dual-microcontroller setup to monitor and transmit water level data at two locations in a lake. The first module, positioned at the center where GSM signal is unavailable, measures water level and temperature, then relays the data via the ESP-NOW protocol to a second module stationed at the lake’s edge. This second unit consolidates the readings and transmits them to a base station using both GSM and Wi-Fi for broader connectivity.

## Project Features:

- Real Time Water-Level and temprature updates
- Accurate Data Measurments using different sensors
- Tracking measurements at two different locations
- Intiutive dashboard displaying data
- GSM connectivity
- Creative UI on Oled inspired by the Flipper Zero UI
- Alarm system if the Water Level is under a specified Limit

## Technical Highlights:

- Uses ESP32 Microcontroller for its wireless capability
- ESP-NOW Protocol used for communication between the two nodes
- GSM Connectivity Sends data to the dashboard in Real-Time.
- Overcoming GSM Challenges using an SMS system.
- Custom designed PCB for Each Node
    - Double Layer for Middle Node
    - Single Layer for Edge Node
- Power Supply filtering circuit to ensure safe operation of all components used
- Measuring water levels using two different methods
    - Ultrasonic Sensor
    - Time of Flight (ToF) Sensor
- Firbase used for storing and collecting data