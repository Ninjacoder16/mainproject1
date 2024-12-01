#include <DHT.h>

#define TRIG_PIN 5   // Define the GPIO pin connected to the Trigger
#define ECHO_PIN 18  // Define the GPIO pin connected to the Echo
// Define DHT type and GPIO pin
#define DHTPIN 4       // GPIO pin where the DHT11 is connected
#define DHTTYPE DHT11  // Specify DHT11 sensor type
#define LED 13         // LED connected to digital pin 13
#define MQ2pin 12      // MQ2 sensor connected to analog pin A0
#define LDR_PIN 14     // Use a suitable ADC pin on the ESP32
#define led_Stree 15


void Ualtrasonic();
void gas_sensor();
void lrd_sensor();
void temp_hum();

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  dht.begin();           // Initialize the DHT sensor
  Serial.println("DHT11 sensor initialized.");
  Serial.println("New addded");  // Set the trigPin as OUTPUT and echoPin as INPUT
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED, OUTPUT);           // Set the LED pin as an output
  pinMode(MQ2pin, INPUT);         // Set the LED pin as an output
  pinMode(LDR_PIN, INPUT);        // Set the LED pin as an output
  digitalWrite(TRIG_PIN, LOW);    // Ensure the trigPin starts LOW
  digitalWrite(led_Stree, HIGH);  // Ensure the trigPin starts LOW
  delay(50);
}

void loop() {
  lrd_sensor();
  temp_hum();
  gas_sensor();
  Ualtrasonic();
  delay(1000);  // Wait for 1 second
}

void temp_hum() {
  delay(2000);  // Wait a few seconds between measurements
  // Reading temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  // Celsius

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print results to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}

void Ualtrasonic() {
  // Send a pulse to the trigger pin to start the ultrasonic sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the pulse duration from the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance based on the duration
  // Speed of sound is 34300 cm/s, so divide by 2 (to account for the round trip)
  float distance = (duration * 0.0343) / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");  // Delay before taking the next reading
  delay(500);
}


void gas_sensor() {
  float sensorValue;                 // Variable to store the sensor value
  sensorValue = analogRead(MQ2pin);  // Read the analog value from the MQ2 sensor

  if (sensorValue >= 250) {   // Check if the sensor value exceeds the threshold
    digitalWrite(LED, HIGH);  // Turn the LED on
    Serial.print(sensorValue);
    Serial.println(" | GAS DETECTED");
  } else {
    digitalWrite(LED, LOW);  // Turn the LED off
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);
  }
  delay(1000);  // Wait for 1 second
}

// Define the analog pin where the LDR is connected

void lrd_sensor() {
  // Read the value from the LDR (0-4095 for ESP32)
  int ldrValue = analogRead(LDR_PIN);  // Convert the ADC value to voltage (optional, based on 3.3V)
  // float voltage = ldrValue * (3.3 / 4095.0);
  if (ldrValue < 0) {
    digitalWrite(led_Stree, LOW);  // Ensure the trigPin starts LOW
  } else {
    digitalWrite(led_Stree, HIGH);  // Ensure the trigPin starts LOW
  }
  Serial.println("LDR Value: ");  // Print the LDR value and voltage to the Serial Monitor
  Serial.println(ldrValue);
  delay(500);  // Delay to slow down readings
}
