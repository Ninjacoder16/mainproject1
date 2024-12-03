#include <WiFi.h>
#include <PubSubClient.h>
   
// Wi-Fi credentials
const char* ssid = "AIRCON1";
const char* password = "LT123456";
      
// MQTT Broker details
const char* mqtt_server = "mqtt-dashboard.com";  // Example: Eclipse public broker, replace with your broker's IP or domain
const int mqtt_port = 1883;  // Default MQTT port
const char* mqtt_user = ""; // MQTT username (optional)
const char* mqtt_password = ""; // MQTT password (optional)
const char* mqtt_topic = "aarti/temp/humidity";  // Topic to which we will publish data

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  setup_wifi();

  // Set MQTT server
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);
}

void loop() {
  // Ensure the MQTT connection is active
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publish data to MQTT broker
  char message[] = "Hello from ESP32!";
  client.publish(mqtt_topic, message);

  delay(5000);  // Wait for 5 seconds before publishing again
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {
  // Loop until connected to the broker
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// MQTT callback function to handle incoming messages
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
