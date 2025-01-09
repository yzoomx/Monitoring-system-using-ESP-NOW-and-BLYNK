#include <esp_now.h>
#include <WiFi.h>

// Define pins for the sensors
#define WATER_SENSOR_PIN 3
#define MOTION_SENSOR_PIN 5

// Define the pin for the onboard LED
const int ledPin = 15;

// Define a structure to store the sensor data
struct Node2Data {
  int id;
  bool waterDetected;
  bool motionDetected;
};

// Create an instance of the Node2Data structure
Node2Data myData;

// Define the MAC address of the central hub
uint8_t hubAddress[] = { 0x78, 0x21, 0x84, 0xC6, 0xD2, 0xEC };

void setup() {
  Serial.begin(115200);

  // Initialize sensor pins
  pinMode(WATER_SENSOR_PIN, INPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);

  // Set the LED pin as an output and initialize it to off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Set the WiFi mode to station mode and disconnect
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Add the central hub as a peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, hubAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Read sensor data
  bool waterDetected = digitalRead(WATER_SENSOR_PIN);
  bool motionDetected = digitalRead(MOTION_SENSOR_PIN);

  // Populate the data structure with sensor data
  myData.id = 2;
  myData.waterDetected = waterDetected;
  myData.motionDetected = motionDetected;

  // Print the sensor data to the serial monitor
  Serial.print("id = ");
  Serial.print(myData.id);
  Serial.print(", waterDetected = ");
  Serial.print(myData.waterDetected);
  Serial.print(", motionDetected = ");
  Serial.print(myData.motionDetected);

  // Send the sensor data to the central hub using ESP-NOW
  esp_err_t result = esp_now_send(hubAddress, (uint8_t *)&myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println(" SUCCESSFULLY");

    // Toggle the LED state
    int ledState = digitalRead(ledPin);
    digitalWrite(ledPin, !ledState);
  } else {
    Serial.println(" FAILED TO SEND");
  }

  // Wait before sending the next data
  delay(500);
}
