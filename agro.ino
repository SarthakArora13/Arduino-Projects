#include <Servo.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2          // Pin connected to DHT11
#define DHTTYPE DHT11     // DHT11 sensor type
#define SOIL_PIN A0       // Pin connected to soil sensor
#define RAIN_PIN 7        // Pin connected to rain sensor
#define ECHO_PIN 4        // Pin connected to ultrasonic sensor echo
#define TRIG_PIN 5        // Pin connected to ultrasonic sensor trigger
#define BUZZER_PIN 8      // Pin connected to buzzer
#define SERVO_PIN 9       // Pin connected to servo motor

// Define thresholds
#define TEMP_HIGH 35
#define TEMP_LOW 15
#define HUMIDITY_HIGH 80
#define HUMIDITY_LOW 20
#define SOIL_MOISTURE_LOW 300
#define SOIL_MOISTURE_HIGH 700
#define RAIN_THRESHOLD 500
#define DISTANCE_THRESHOLD 20 // 20 cm for ultrasonic detection

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize sensors and components
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();
  
  pinMode(SOIL_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  myServo.attach(SERVO_PIN);
  myServo.write(90); // Start servo at 90 degrees
  
  lcd.setCursor(0, 0);
  lcd.print("System Init...");
  delay(2000);
}

void loop() {
  // Read sensors
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int soilMoisture = analogRead(SOIL_PIN);
  int rain = digitalRead(RAIN_PIN);

  // Measure distance using ultrasonic sensor
  float distance = measureDistance();

  // Update display with temperature and humidity continuously
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");
  
  delay(2000); // Display temp & humidity for 2 seconds

  // Check environmental conditions
  if (temperature > TEMP_HIGH || temperature < TEMP_LOW) {
    showAlert("Temp out of range!");
  }
  
  if (humidity > HUMIDITY_HIGH || humidity < HUMIDITY_LOW) {
    showAlert("Humidity warning!");
  }
  
  if (soilMoisture < SOIL_MOISTURE_LOW || soilMoisture > SOIL_MOISTURE_HIGH) {
    showAlert("Soil Moisture alert!");
  }
  
  if (rain > RAIN_THRESHOLD) {
    showAlert("Rain detected!");
  }

  // Check for object using ultrasonic sensor
  myServo.write(90); // Servo at 90 degrees
  delay(500);

  if (distance < DISTANCE_THRESHOLD) {
    // Obstacle detected, sound buzzer and show alert
    tone(BUZZER_PIN, 1000); // Buzzer on
    showAlert("Object detected!");
    noTone(BUZZER_PIN);     // Buzzer off
  }
}

// Function to measure distance using ultrasonic sensor
float measureDistance() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo pin and calculate the distance
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// Function to show alerts temporarily on the LCD
void showAlert(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALERT:");
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(3000); // Show alert for 3 seconds
}
