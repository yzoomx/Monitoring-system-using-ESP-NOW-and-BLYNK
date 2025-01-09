// Define Blynk template ID and authentication token
#define BLYNK_TEMPLATE_ID "TMPL6nUxJujWn"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "hQcHtb4RUVBz0ZXlJzAj2G5qQ2EogP7a"

// Define BLYNK_PRINT to use Serial for debugging
#define BLYNK_PRINT Serial

// Include necessary libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define the pin for the onboard LED
const int ledPin = 2;

// WiFi credentials
char ssid[] = "ESP32";
char pass[] = "6789054321";

// Define virtual pins for Blynk
#define gas_vpin V1
#define temperature_vpin V2
#define humidity_vpin V3
#define motion_vpin V4
#define waterLvl_vpin V5

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Initialize the LED state to HIGH (LED off, as it is active low)
  digitalWrite(ledPin, HIGH);

  // Start Serial for communication with ESP32 and for debug
  Serial.begin(9600);

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // Check if there is data available on the serial port
  if (Serial.available() > 0) {
    // Read the incoming data
    String data = Serial.readStringUntil('\n');
    int temperature, humidity;
    int gas;
    int motion, waterPresence;

    // Parse the received data
    sscanf(data.c_str(), "%d-%d-%d-%d-%d", &temperature, &humidity, &gas, &motion, &waterPresence);

    // Print the received values to the Serial Monitor
    Serial.print("Received values: ");
    Serial.print(temperature);
    Serial.print(", ");
    Serial.print(humidity);
    Serial.print(", ");
    Serial.print(gas);
    Serial.print(", ");
    Serial.print(motion);
    Serial.print(", ");
    Serial.println(waterPresence);

    // Send the parsed values to Blynk virtual pins
    Blynk.virtualWrite(temperature_vpin, temperature);
    Blynk.virtualWrite(humidity_vpin, humidity);
    Blynk.virtualWrite(gas_vpin, gas);
    Blynk.virtualWrite(motion_vpin, motion);
    Blynk.virtualWrite(waterLvl_vpin, waterPresence);

    // Read the current state of the LED pin
    int currentState = digitalRead(ledPin);

    // Toggle the LED state
    if (currentState == LOW) {
      digitalWrite(ledPin, HIGH); // Turn LED off
    } else {
      digitalWrite(ledPin, LOW); // Turn LED on
    }
  }
}