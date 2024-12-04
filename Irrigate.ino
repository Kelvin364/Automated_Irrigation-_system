#include <LiquidCrystal.h>
#include <Servo.h>

// Pin definitions
#define MOISTURE_SENSOR A0
#define SERVO_PIN 9
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo waterValve;

// System parameters
const int DRY_THRESHOLD = 500;     // Adjust based on your sensor calibration
const int WET_THRESHOLD = 300;     // Adjust based on your sensor calibration
const int WATERING_TIME = 5000;    // Watering duration in milliseconds
const int CHECK_INTERVAL = 1800000; // Check every 30 minutes (in milliseconds)
const int SERVO_CLOSED = 0;        // Servo angle for closed valve
const int SERVO_OPEN = 90;         // Servo angle for open valve

// Global variables
int moistureLevel;
unsigned long lastWateringTime = 0;
bool isWatering = false;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Irrigation System");
  delay(2000);
  
  // Initialize servo
  waterValve.attach(SERVO_PIN);
  waterValve.write(SERVO_CLOSED);
  
  // Initialize analog pin for moisture sensor
  pinMode(MOISTURE_SENSOR, INPUT);
}

void loop() {
  // Read moisture level
  moistureLevel = analogRead(MOISTURE_SENSOR);
  
  // Map moisture level to percentage for display
  int moisturePercent = map(moistureLevel, 0, 1023, 100, 0);
  
  // Update LCD display
  updateDisplay(moisturePercent);
  
  // Check if it's time to water
  if (shouldWater()) {
    waterPlants();
  }
  
  // If currently watering, check if watering duration is complete
  if (isWatering && (millis() - lastWateringTime >= WATERING_TIME)) {
    stopWatering();
  }
  
  // Print debug information to Serial Monitor
  Serial.print("Moisture Level: ");
  Serial.print(moisturePercent);
  Serial.println("%");
  
  delay(1000); // Delay between readings
}

bool shouldWater() {
  // Check if soil is dry and enough time has passed since last watering
  return (moistureLevel > DRY_THRESHOLD && 
          !isWatering && 
          (millis() - lastWateringTime >= CHECK_INTERVAL));
}

void waterPlants() {
  isWatering = true;
  lastWateringTime = millis();
  
  // Open valve
  waterValve.write(SERVO_OPEN);
  
  // Update LCD
  lcd.clear();
  lcd.print("Watering Plants");
  lcd.setCursor(0, 1);
  lcd.print("Please wait...");
}

void stopWatering() {
  isWatering = false;
  
  // Close valve
  waterValve.write(SERVO_CLOSED);
  
  // Update LCD
  lcd.clear();
  lcd.print("Watering Complete");
  delay(2000);
}

void updateDisplay(int moisturePercent) {
  if (!isWatering) {
    lcd.clear();
    lcd.print("Moisture: ");
    lcd.print(moisturePercent);
    lcd.print("%");
    lcd.setCursor(0, 1);
    
    // Display status message based on moisture level
    if (moisturePercent < 30) {
      lcd.print("Soil is DRY");
    } else if (moisturePercent < 70) {
      lcd.print("Soil is GOOD");
    } else {
      lcd.print("Soil is WET");
    }
  }
}