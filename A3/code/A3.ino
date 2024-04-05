#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD and MPU6050
LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_MPU6050 mpu;
char timerStr[16]; // Buffer for the timer string

// Buzzer Pin
int buzzerPin = 12;

// Motor control pins
int enB = 10;
int enA = 9;
int in1 = 8;
int in2 = 7;
int in3 = 6;
int in4 = 5;

// Button setup
int startButtonPin = 2;
int pauseButtonPin = 3;
int resetButtonPin = 4;

// Timer variables
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
bool timerRunning = false;
bool timerPaused = false;

// Store initial Z-axis acceleration
float initialZ = 0;

bool pomodoroBreak = false;

void setup(void)
{
    Serial.begin(9600);
    while (!Serial)
        delay(10); // wait for serial port to connect. Needed for native USB

    lcd.init(); // initialize the lcd
    lcd.init();
    lcd.backlight(); // Turn on the backlight

    pinMode(buzzerPin, OUTPUT);

    // Display starting text
    lcd.setCursor(0, 0);
    lcd.print("Press Green BTN");
    lcd.setCursor(0, 1);
    lcd.print("To Start Timer");

    // Set solenoid pin to output
    pinMode(10, OUTPUT);

    // Set motor pins as outputs
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    // Setup the button pins with internal pull-up resistors
    pinMode(startButtonPin, INPUT);
    pinMode(pauseButtonPin, INPUT);
    pinMode(resetButtonPin, INPUT);

    // Initialize the MPU6050
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
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

void controlMotor()
{
    if (timerRunning && !timerPaused)
    { // Check if the timer is running and not paused
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        float deltaZ = a.acceleration.z - initialZ; // Calculate the change in Z-axis acceleration
        float movementThreshold = 0.2;              // Define a threshold for movement

        // If the change in Z-axis acceleration exceeds the threshold, turn the motor on
        if (abs(deltaZ) > movementThreshold)
        {
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            analogWrite(enA, 255); // Run motor at full speed
        }
        else
        {
            // Otherwise, stop the motor
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            analogWrite(enA, 0); // Stop the motor
        }
    }
    else
    {
        // If the timer is not running or paused, ensure the motor is off
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(enA, 0); // Stop the motor
    }
}

void loop()
{
    checkButtons();
    updateTimer();
    updateDisplay();
    controlMotor();
    delay(100); // Loop delay for stability
}

void checkButtons()
{
    // Check if the start button is pressed (active high)
    if (digitalRead(startButtonPin) == HIGH)
    {
        delay(50); // Debounce delay
        if (digitalRead(startButtonPin) == HIGH)
        {
            Serial.println("Start button pressed");
            analogWrite(enB, 255); // Close solenoid valve
            startTimer();
            while (digitalRead(startButtonPin) == HIGH)
                ; // Wait for button release
        }
    }

    // Check if the pause button is pressed (active high)
    if (digitalRead(pauseButtonPin) == HIGH)
    {
        delay(50); // Debounce delay
        if (digitalRead(pauseButtonPin) == HIGH)
        {
            Serial.println("Pause button pressed");
            pauseTimer();
            while (digitalRead(pauseButtonPin) == HIGH)
                ; // Wait for button release
        }
    }

    // Check if the reset button is pressed (active high)
    if (digitalRead(resetButtonPin) == HIGH)
    {
        delay(50); // Debounce delay
        if (digitalRead(resetButtonPin) == HIGH)
        {
            analogWrite(enB, 0); // Open solenoid valve
            Serial.println("Reset button pressed");
            resetTimer();
            while (digitalRead(resetButtonPin) == HIGH)
                ; // Wait for button release
        }
    }
}

void startTimer()
{
    lcd.clear(); // Clear the display when starting the timer
    startTime = millis();
    timerRunning = true;
    timerPaused = false;
    playStartSound(); // Play the start sound
}

void pauseTimer()
{
    if (timerRunning)
    {
        timerPaused = !timerPaused;
        if (timerPaused)
        {
            lcd.setCursor(0, 1);
            lcd.print("Timer Paused  ");
        }
        else
        {
            lcd.setCursor(0, 1);
            lcd.print("               ");
        }
    }
}

void playStartSound()
{
    tone(buzzerPin, 1000, 200); 
    delay(200);
    tone(buzzerPin, 1500, 200);
    delay(200);
}

void playBreakChime()
{
    tone(buzzerPin, 1000, 500);
    delay(500);
    tone(buzzerPin, 1500, 500); 
    delay(500);
    tone(buzzerPin, 2000, 1000);
    delay(1000);
}

void updateTimer()
{
    if (timerRunning && !timerPaused)
    {
        elapsedTime = millis() - startTime;

        // Check if the work session has ended (25 minutes)
        if (elapsedTime >= 25 * 60 * 1000 && !pomodoroBreak)
        {
            pomodoroBreak = true;
            startTime = millis(); // Reset the start time for the break session
            elapsedTime = 0;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Break Time!");
            playBreakChime();
        }
        // Check if the break session has ended (5 minutes)
        else if (elapsedTime >= 5 * 60 * 1000 && pomodoroBreak)
        {
            pomodoroBreak = false;
            startTime = millis(); // Reset the start time for the next work session
            elapsedTime = 0;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Work Time!");
        }
    }
    else if (timerRunning && timerPaused)
    {
        // Timer is paused, so we need to adjust the start time
        startTime = millis() - elapsedTime;
    }
}

void resetTimer()
{
    timerRunning = false;
    timerPaused = false;
    pomodoroBreak = false;
    elapsedTime = 0;

    // Stop the motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0);

    // Reset the Z-axis of the MPU6050
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    initialZ = a.acceleration.z;

    // Display starting text when resetting the timer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press Green BTN ");
    lcd.setCursor(0, 1);
    lcd.print("To Start Timer");
}

void updateDisplay()
{
    if (timerRunning)
    {
        lcd.setCursor(0, 0);
        if (pomodoroBreak)
        {
            lcd.print("Break Time!     ");
        }
        else
        {
            lcd.print("Work Time!      ");
        }

        int minutes = (elapsedTime / 1000) / 60;
        int seconds = (elapsedTime / 1000) % 60;

        sprintf(timerStr, "%02d:%02d", minutes, seconds);
        lcd.setCursor(0, 1);
        lcd.print(timerStr);
    }
}
