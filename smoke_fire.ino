#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int smokeSensorPin = A0;  // Analog pin for MQ-5
const int fireSensorPin = 2;    // Digital pin for fire sensor
const int buzzerPin = 8;        // Buzzer pin

// Threshold values (can be adjusted based on sensor sensitivity)
int smokeThreshold = 400;  // Analog threshold for MQ-5

void setup() {
  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  
  // Initialize sensor and buzzer pins
  pinMode(smokeSensorPin, INPUT);
  pinMode(fireSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Print initial message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Monitoring...");
  lcd.setCursor(0, 1);
  lcd.print("Smoke & Fire");
}

void loop() {
  // Read sensor values
  int smokeValue = analogRead(smokeSensorPin);
  int fireValue = digitalRead(fireSensorPin);

  // Check smoke levels
  if (smokeValue > smokeThreshold) {
    alert("Smoke Detected!");
  }
  // Check fire sensor
  else if (fireValue == LOW) {  // Fire sensor is active-low
    alert("Fire Detected!");
  } 
  // No danger detected
  else {
    noAlert();
  }

  delay(500);  // Wait for half a second before the next reading
}

void alert(String message) {
  // Display warning message on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);

  // Activate the buzzer
  digitalWrite(buzzerPin, HIGH);
}

void noAlert() {
  // Clear any alert message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Monitoring...");
  lcd.setCursor(0, 1);
  lcd.print("Smoke & Fire");

  // Deactivate the buzzer
  digitalWrite(buzzerPin, LOW);
}
