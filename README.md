# Smart Home Monitoring Project


## Course Instructor
**Öğr. Gör. Dr. MHD WASIM RAED**

## Project Overview
This project, titled "Home Automation using Microcontrollers," aims to develop an advanced home automation system that integrates multiple sensors to monitor environmental conditions and security parameters. The primary goal is to create a cohesive and efficient network that enhances the convenience and safety of modern living spaces.

By leveraging the capabilities of microcontrollers and employing local and remote monitoring through the Blynk app, the project demonstrates the practical applications of IoT in home automation. The system ensures that users are always informed about their home environment, providing a comprehensive and innovative solution for smart home management.

## Hardware Components
The project uses the following microcontrollers:
- **ESP32 LOLIN S2 Mini**: Used in Node 1 and Node 2 for data collection from sensors.
- **ESP32 Node32S**: Acts as the central hub to receive data from nodes via ESP-NOW protocol.
- **ESP8266 LolinMCU v3**: Interfaces with the Blynk cloud platform to visualize and control the system.

## Sensors and Their Functions
- **DHT22 Temperature and Humidity Sensor**: Installed in Node 1 to measure environmental temperature and humidity.
- **Water Detection Sensor**: Installed in Node 2 to detect water presence.
- **Motion Sensor**: Also in Node 2, to detect motion.

## Software and Communication Protocols
- **ESP-NOW Protocol**: Used for wireless communication between Node 1, Node 2, and the central hub (ESP32 Node32S).
- **UART Serial Communication**: For data transfer from the central hub to the ESP8266 LolinMCU v3.
- **Blynk Cloud Platform**: For real-time monitoring and control through a user-friendly interface.

## Code Implementation
### Node 1 Code Overview
1. **Library Inclusions and Definitions**: Includes libraries for ESP-NOW, Wi-Fi, and DHT sensor. Sets up GPIO pins for the sensor and LED.
2. **Global Variables and Structures**: Defines the structure for sensor data and initializes the DHT sensor.
3. **Setup Function**: Initializes serial communication, sensor, Wi-Fi, and ESP-NOW. Adds the central hub as a peer.
4. **Loop Function**: Reads sensor data, sends it to the central hub, and toggles the LED based on transmission success.

### Node 2 Code Overview
1. **Library Inclusions and Pin Definitions**: Includes necessary libraries and sets up GPIO pins for the sensors and LED.
2. **Global Variables and Structures**: Defines the structure for sensor data and initializes the pins.
3. **Setup Function**: Initializes serial communication, sensor pins, Wi-Fi, and ESP-NOW. Adds the central hub as a peer.
4. **Loop Function**: Reads sensor data, sends it to the central hub, and toggles the LED based on transmission success.

### Central Hub Code Overview
1. **Library Inclusions and Pin Definitions**: Sets up libraries and pins for communication.
2. **Global Variables and Structures**: Defines structures for receiving data from nodes.
3. **Setup Function**: Initializes serial communication and ESP-NOW for receiving data.
4. **Loop Function**: Receives data from nodes and forwards it to the ESP8266 for Blynk integration.

## Usage Instructions
1. **Hardware Setup**: Connect the sensors to the respective microcontrollers as per the wiring diagrams provided in the report.
2. **Upload Code**: Upload the provided code to the ESP32 LOLIN S2 Mini, ESP32 Node32S, and ESP8266 LolinMCU v3 using Arduino IDE.
3. **Run the System**: Power up the system and monitor the data on the Blynk app.

## Additional Information
For detailed hardware setup, software configurations, and troubleshooting, please refer to the project report.
