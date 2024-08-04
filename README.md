# Smart Greenhouse Project

## Overview

This Arduino-based smart greenhouse system is designed to monitor and control environmental conditions to optimize plant growth. The system utilizes various sensors to measure light intensity, soil moisture, temperature, humidity, and water tank levels. It also includes motion detection for security and automation purposes.

## Features

- **Light Intensity Control:** Uses an LDR sensor and a PID controller to maintain optimal lighting conditions.
- **Soil Moisture Monitoring:** Ensures that plants receive the right amount of water.
- **Temperature and Humidity Monitoring:** Utilizes a DHT11 sensor to keep track of environmental conditions.
- **Water Level Monitoring:** An ultrasonic sensor measures the water tank level, with visual feedback provided by an RGB LED.
- **Motion Detection:** Employs a PIR sensor for detecting movement within the greenhouse.
- **Real-time Data Output:** Outputs sensor data to the serial monitor for real-time monitoring and analysis.

## Components

- **Arduino Board:** Central controller for the system.
- **LDR Sensor (Light Dependent Resistor):** Measures ambient light intensity.
- **Soil Moisture Sensor:** Detects soil moisture levels.
- **PIR Sensor (Passive Infrared Sensor):** Detects motion.
- **DHT11 Sensor:** Measures temperature and humidity.
- **Ultrasonic Sensor:** Determines the water level in the tank.
- **RGB LED:** Indicates water tank level.
- **Light Control Module:** Manages lighting intensity.
- **PID Controller:** Maintains desired lighting conditions.

## Wiring Diagram

Below is a simple representation of the wiring connections:

1. **LDR Sensor:**
   - Connect to analog pin A0.
   - Connect VCC to 5V.

2. **Soil Moisture Sensor:**
   - Connect to analog pin A1.
   - Connect VCC to 5V.

3. **PIR Sensor:**
   - Connect to digital pin 2.

4. **DHT11 Sensor:**
   - Connect to digital pin 4.

5. **Ultrasonic Sensor:**
   - Trigger pin: connect to pin 7.
   - Echo pin: connect to pin 8.

6. **RGB LED:**
   - Red pin: connect to pin 3.
   - Green pin: connect to pin 5.
   - Blue pin: connect to pin 6.

7. **Light Control Module:**
   - Control pin: connect to pin 10.

## Installation

### Prerequisites

- **Hardware:** Arduino board (e.g., Arduino Uno), various sensors, and modules as listed in the components section.
- **Software:** Arduino IDE installed on your computer.
- **Libraries Required:**
  - `DHT.h`
  - `PID_v1.h`
  - Custom sensor libraries: `ldr.h`, `soilMoisture.h`, `pir.h`, `rgbLED.h`, `lightControl.h`, `ultrasonicSensor.h`

### Setup

1. **Clone the Repository:**

   Clone the repository to your local machine using the following command:

   ```bash
   git clone https://github.com/yourusername/smart-greenhouse.git

## Future Improvements

- **Automated Watering:** Implement an automated watering system based on soil moisture readings.
- **Remote Monitoring:** Develop a web-based interface for remote monitoring and control of the greenhouse environment.
- **Enhanced Security:** Add more sensors for comprehensive security monitoring.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Acknowledgments
- **Arduino Community:** Thanks to the Arduino community for providing open-source resources and support.
- **Contributors:** A special thanks to all contributors and collaborators on this project.
