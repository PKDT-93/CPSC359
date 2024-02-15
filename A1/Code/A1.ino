#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>
BLEMIDI_CREATE_INSTANCE("Arduino", MIDI);

int potPin = 34; // Analog input pin connected to the potentiometer
int lastPotValue = -1; // Store the last potentiometer value to detect significant movement
int threshold = 100; // Global threshold value for triggering notes

void setup() {å
    MIDI.begin(10);  // Listen to all incoming messages
    // Initialize pins as analog input for triggering notes
    pinMode(15, INPUT);
    pinMode(0, INPUT);
    pinMode(4, INPUT);
    pinMode(2, INPUT);ß
    // Initialize the potentiometer pin as input
    pinMode(potPin, INPUT);
    pinMode(25, OUTPUT); // Set GPIO pin 25 as an output for the LED
    Serial.begin(115200);
    Serial.println("Setup complete");
}

void loop() {
    // Read the analog input from the potentiometer
    int potValue = analogRead(potPin);
    // Map the potentiometer value to select the base note of the chromatic scale (e.g., 48-60)
    int baseNote = map(potValue, 0, 4095, 48, 60);

    // Print potentiometer movement and new base note if it changes significantly
    if (abs(potValue - lastPotValue) > 10) { // Adjust for sensitivity
        Serial.print("Base note changed to: ");
        Serial.println(baseNote);
        lastPotValue = potValue; // Update the last potentiometer value
    }

    // Read the analog input from each pin
    int sensorValue15 = analogRead(15);
    int sensorValue0 = analogRead(0);
    int sensorValue4 = analogRead(4);
    int sensorValue2 = analogRead(2);

    // Check each sensor and send a MIDI note if below threshold
    // The notes are consecutive in the chromatic scale starting from the base note
    checkSensorAndSendMidi(sensorValue15, baseNote); // First sensor plays the base note
    checkSensorAndSendMidi(sensorValue0, baseNote + 1); // Second plays the next chromatic note
    checkSensorAndSendMidi(sensorValue4, baseNote + 2); // Third plays the next
    checkSensorAndSendMidi(sensorValue2, baseNote + 3); // Fourth plays the next

    delay(100); // Short delay to prevent too frequent readings
}

void checkSensorAndSendMidi(int sensorValue, int note) {
    static int lastNote = -1; // Remember the last note played to avoid repeating the same note
    if (sensorValue < threshold) {
        if (note != lastNote) { // Play the note if it's different from the last note
            Serial.print("Sending MIDI note on message for note ");
            Serial.println(note);
            MIDI.sendNoteOn(note, 127, 1); // Send specified note on channel 1
            digitalWrite(25, HIGH); // Turn on the LED
            delay(100); // Wait a bit to simulate the note being played
            digitalWrite(25, LOW); // turn off the LED 
            lastNote = note; // Update the last note played
        }
    } else if (lastNote != -1) { // No sensor is activated, and there was a previous note
        MIDI.sendNoteOff(lastNote, 0, 1); // Turn off the last note
        // digitalWrite(25, LOW); // Optionally, ensure the LED is off when no note is active
        lastNote = -1; // Reset the last note
    }
}

