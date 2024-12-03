#include <HardwareSerial.h>

// Define hardware serial port for A9 module
HardwareSerial A9Serial(2); // Use UART2 on ESP32

// GPIO Pins for A9 module
#define RXD2 16 // ESP32 RX (connect to A9 TX)
#define TXD2 17 // ESP32 TX (connect to A9 RX)

void setup() {
  // Start Serial Monitor for debugging
  Serial.begin(115200);
  Serial.println("ESP32 is starting...");

  // Initialize A9 Serial communication
  A9Serial.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Initializing A9 module...");
  
  // Test communication with A9 module
  testA9Module();
}

void loop() {
  // Continuously listen for responses from A9 module
  if (A9Serial.available()) {
    String response = A9Serial.readString();
    Serial.println("A9 Response: " + response);
  }
}

void testA9Module() {
  // Send AT command to A9 module
  A9Serial.println("AT");
  Serial.println("Sent: AT");

  delay(1000); // Wait for response

  // Check for response
  if (A9Serial.available()) {
    String response = A9Serial.readString();
    Serial.println("A9 Module Response: " + response);
  } else {
    Serial.println("No response from A9 module. Check connections and power.");
  }
}
