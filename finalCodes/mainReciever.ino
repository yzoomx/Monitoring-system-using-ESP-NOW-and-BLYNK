#include <WiFi.h>
#include <esp_now.h>
#include <HardwareSerial.h>

// Create a serial instance for UART communication
HardwareSerial mySerial(2);

// Define the pin for the gas sensor
const int gasSensorPin = 39;

// Define the pin for the onboard LED
const int ledPin = 2;

// Variables to store sensor data
int gazz = 0, temp = 0, hum = 0, mot = 0, wat = 0;

// Define structures to store data from Node 1 and Node 2
struct Node1Data {
  int id;
  float temperature;
  float humidity;
};

struct Node2Data {
  int id;
  bool waterDetected;
  bool motionDetected;
};

// Create instances of the data structures
Node1Data node1Data;
Node2Data node2Data;

// Callback function to handle incoming data from ESP-NOW
void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  // Check the source of the data (Node 1 or Node 2)
  if (incomingData[0] == 1) {
    // Data from Node 1 (Temperature and Humidity)
    memcpy(&node1Data, incomingData, sizeof(node1Data));
    temp = (int)node1Data.temperature;
    hum = (int)node1Data.humidity;
  } else if (incomingData[0] == 2) {
    // Data from Node 2 (Water and Motion)
    memcpy(&node2Data,incomingData, sizeof(node2Data));
    mot = node2Data.motionDetected;
    wat = node2Data.waterDetected;
  }
}

void setup() {
  Serial.begin(115200);

  // Start the UART serial communication
  mySerial.begin(9600, SERIAL_8N1, 16, 17);

  // Set the gas sensor pin as input
  pinMode(gasSensorPin, INPUT);

  // Set the LED pin as an output and initialize it to off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Set the WiFi mode to station mode
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the callback function for receiving data
  esp_now_register_recv_cb(onDataRecv);

  // Debug print to confirm setup
  Serial.println("Setup complete, starting loop...");
}

void loop() {
  // Read the gas sensor value
  gazz = analogRead(gasSensorPin);

  // Print the received sensor data
  Serial.printf("Temp: %d, Hum: %d, Gas: %d, Motion: %d, Water: %d\n", temp, hum, gazz, mot, wat);

  // Send the sensor data to the ESP8266 board via UART
  mySerial.print(temp);
  mySerial.print("-");
  mySerial.print(hum);
  mySerial.print("-");
  mySerial.print(gazz);
  mySerial.print("-");
  mySerial.print(mot);
  mySerial.print("-");
  mySerial.println(wat);

  // Toggle the LED state
  int ledState = digitalRead(ledPin);
  digitalWrite(ledPin, !ledState);

  delay(1000);
}

