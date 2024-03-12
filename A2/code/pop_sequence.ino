#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD and MPU6050
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MPU6050 mpu;
char newTimeStr[16]; // Buffer for the new time string

// Motor control pins
int enA = 9;
int in1 = 8;
int in2 = 7;

// Button setup
int buttonState = 0;
int lastButtonState = HIGH; // Assume button starts unpressed
int buttonPin = 2;

// Variable to track if the new time should be displayed
bool showTime = false;
bool timeCaptured = false; // Flag to check if the time has been captured
String dateTime = ""; // Global scope to capture the time only once

// Store initial Z-axis acceleration
float initialZ = 0;

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);
  lcd.init(); 
  lcd.backlight();

  // Set motor pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Setup the button pin with an internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize the MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // Configure the MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  delay(1000); // Let sensor stabilize

  // Get an initial reading from the MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  initialZ = a.acceleration.z;

  Serial.println("MPU6050 configuration done.");
}

void controlMotor() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float deltaZ = a.acceleration.z - initialZ; // Calculate the change in Z-axis acceleration
  float movementThreshold = 0.2; // Define a threshold for movement

  // If the change in Z-axis acceleration exceeds the threshold, turn the motor on
  if (abs(deltaZ) > movementThreshold) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255); // Run motor at full speed
  } else {
    // Otherwise, stop the motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0); // Stop the motor
  }
}

void loop() {
  checkButton();
  updateDisplay();
  controlMotor();
  delay(100); // Loop delay for stability
}

void checkButton() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    delay(50); // Debounce delay
    if (reading == LOW && lastButtonState == HIGH) { // Button press detected
      if (!timeCaptured && Serial.available() > 0) {
        // Capture the current time once
        dateTime = Serial.readStringUntil('\n');
        timeCaptured = true;
      }
      showTime = !showTime; // Toggle the showTime flag
    }
    lastButtonState = reading; // Update the lastButtonState
  }
}

void updateDisplay() {
  if (timeCaptured && showTime && dateTime.length() > 0) {
    // Process and display the new time only if the time has been captured and showTime is true
    int hour = dateTime.substring(0, 2).toInt();
    int minute = dateTime.substring(3, 5).toInt();

    // Calculate the new time by adding 25 minutes
    minute += 25;
    if (minute >= 60) {
      hour += minute / 60;
      minute %= 60;
    }
    // Ensure hour is in 0-23 range
    hour %= 24; 

    sprintf(newTimeStr, "Study: %02d:%02d", hour, minute); // Format the new time string
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Time: " + dateTime); // Display the original dateTime
    lcd.setCursor(0, 1); // Set cursor to the second line for the new time
    lcd.print(newTimeStr); // Display the new time string
  } else if (!showTime) {
    lcd.clear(); // Clear the entire display
    lcd.setCursor(0, 0); // Optionally, redisplay the original time on the first line
    lcd.print("Time: " + dateTime); // Display the original dateTime
  }
}
