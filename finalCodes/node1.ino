#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>

// Define the pin and sensor type for the DHT22 sensor
#define DHTPIN 5    
#define DHTTYPE DHT22

// Create an instance of the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Define the pin for the onboard LED
const int ledPin = 15;

// Define a structure to store the sensor data
struct Node1Data {
  int id;
  float temperature;
  float humidity;
};

// Create an instance of the Node1Data structure
Node1Data myData;

// Define the MAC address of the central hub
uint8_t hubAddress[] =  {0x78, 0x21, 0x84, 0xC6, 0xD2, 0xEC};

void setup() {
  Serial.begin(115200);

  // Set the LED pin as an output and initialize it to off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Initialize the DHT sensor
  dht.begin();

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
  // Read temperature and humidity from the DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if the sensor readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Populate the data structure with sensor data
  myData.id = 1;
  myData.temperature = temperature;
  myData.humidity = humidity;

  // Print the sensor data to the serial monitor
  Serial.print("id = ");
  Serial.print(myData.id);
  Serial.print(", temperature = ");
  Serial.print(myData.temperature);
  Serial.print(", humidity = ");
  Serial.print(myData.humidity);

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
