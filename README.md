# Automated Plant Irrigation System
An Arduino-based automated irrigation system that monitors soil moisture levels and waters plants automatically when needed. The system uses a soil moisture sensor to detect when plants need water and controls a servo-operated valve to dispense water through irrigation pipes.

## Features
- Real-time soil moisture monitoring
- Automatic watering based on moisture thresholds
- LCD display showing current moisture levels and system status
- Configurable watering duration and check intervals
- Servo-controlled water valve
- Debug information via Serial Monitor

## Hardware Requirements
- Arduino Uno board
- 16x2 LCD display
- Soil moisture sensor
- Servo motor
- Water pipes and connections
- Jumper wires
- Breadboard (for prototyping)
- Power supply (5V for Arduino)

## Pin Connections
### LCD Display
- RS pin -> Digital pin 12
- Enable pin -> Digital pin 11
- D4 -> Digital pin 5
- D5 -> Digital pin 4
- D6 -> Digital pin 3
- D7 -> Digital pin 2
- VSS -> GND
- VDD -> 5V
- V0 -> 10K potentiometer middle pin (for contrast adjustment)
- A -> 5V (backlight)
- K -> GND (backlight)

### Soil Moisture Sensor
- VCC -> 5V
- GND -> GND
- Analog Output -> A0

### Servo Motor
- Signal wire -> Digital pin 9
- VCC -> 5V
- GND -> GND

## Software Dependencies
The following Arduino libraries are required:
```cpp
#include <LiquidCrystal.h>
#include <Servo.h>
```

## Installation
1. Connect all components according to the pin connections listed above
2. Install the required libraries through Arduino IDE Library Manager
3. Upload the provided code to your Arduino Uno
4. Calibrate the moisture sensor thresholds (see Configuration section)

## Configuration
Adjust these parameters in the code based on your needs:
```cpp
const int DRY_THRESHOLD = 500;     // Adjust based on your sensor calibration
const int WET_THRESHOLD = 300;     // Adjust based on your sensor calibration
const int WATERING_TIME = 5000;    // Watering duration in milliseconds
const int CHECK_INTERVAL = 1800000; // Check every 30 minutes
```

### Calibrating the Moisture Sensor
1. Insert sensor in completely dry soil and note the reading
2. Insert sensor in sufficiently wet soil and note the reading
3. Adjust DRY_THRESHOLD and WET_THRESHOLD based on these readings

## Usage
1. Power up the system
2. The LCD will display the current moisture level as a percentage
3. The system will automatically water plants when:
   - Soil moisture drops below DRY_THRESHOLD
   - Sufficient time has passed since last watering (CHECK_INTERVAL)
4. Monitor the Serial output (9600 baud) for debugging information

## Troubleshooting
### Common Issues and Solutions
1. Incorrect Moisture Readings
   - Check sensor connections
   - Verify sensor is properly inserted in soil
   - Recalibrate thresholds

2. LCD Display Issues
   - Adjust contrast using potentiometer
   - Verify pin connections
   - Check power supply voltage

3. Servo Not Moving
   - Verify power supply can handle servo current draw
   - Check servo connections
   - Test servo with a basic sweep program

## Safety Considerations
- Keep electronic components away from water
- Use appropriate waterproofing for outdoor installations
- Install a water overflow prevention mechanism
- Regular maintenance checks recommended
- Ensure proper power supply rating

## Maintenance
- Clean moisture sensor periodically
- Check for water leaks in pipes
- Verify servo operation monthly
- Recalibrate moisture sensor every few months
- Update thresholds based on seasonal changes

![alt text](<WhatsApp Image 2024-12-04 at 23.03.35_b0e21eee.jpg>)

