#include <DHT.h>
     
#define TRIG_PIN 5  // Define the GPIO pin connected to the Trigger
#define ECHO_PIN 18 // Define the GPIO pin connected to the Echo
// Define DHT type and GPIO pin
#define DHTPIN 4      // GPIO pin where the DHT11 is connected
#define DHTTYPE DHT11 // Specify DHT11 sensor type
void Ualtrasonic();
// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); // Initialize serial communication
  dht.begin();          // Initialize the DHT sensor
  Serial.println("DHT11 sensor initialized.");
  Serial.println("New addded");
  // Set the trigPin as OUTPUT and echoPin as INPUT
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Ensure the trigPin starts LOW
  digitalWrite(TRIG_PIN, LOW);
  delay(50);
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Reading temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // Check if readings are valid
 /* if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }*/

  // Print results to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Ualtrasonic();
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
  Serial.println(" cm");
  // Delay before taking the next reading
  delay(500);
}


