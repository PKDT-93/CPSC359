// Instructions from https://docs.sunfounder.com/projects/esp32-starter-kit/en/latest/arduino/basic_projects/ar_ac_buz.html were used to control the buzzer
// Song frequencies generated with ChatGPT

const int LED_BUILTIN = 26;
const int BUTTON_PIN = 14;
const int BUZZER_PIN = 27; 
const int resolution = 8;

int FREQUENCIES[] = {262, 262, 392, 392, 440, 440, 392, 349, 349, 330, 330, 294, 294, 262, 392, 392, 349, 349, 330, 330, 294, 392, 392, 349, 349, 330, 330, 294, 262, 262, 392, 392, 440, 440, 392, 349, 349, 330, 330, 294, 294, 262};
const int FREQUENCY_LENGTH = sizeof(FREQUENCIES) / sizeof(FREQUENCIES[0]);
int button_state = 0;

// Function to play a frequency on the buzzer for a given duration
void playFrequency(int frequency, int duration)
{
  ledcWriteTone(0, frequency);     // Start the tone
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
  delay(duration);                 // Wait for the specified duration
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
  ledcWriteTone(0, 0);             // Stop the buzzer
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  ledcSetup(0, 2000, resolution); // Set up the PWM channel
  ledcAttachPin(BUZZER_PIN, 0);   // Attach the buzzer pin to the PWM channel

  // init digital pin LED_BUILTIN as an output and BUTTON_PIN as OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, OUTPUT);
}

void loop()
{
  button_state = digitalRead(BUTTON_PIN);
  delay(50);
  if (button_state == HIGH)
  {
    for (int i = 0; i < FREQUENCY_LENGTH; i++)
    {
      playFrequency(FREQUENCIES[i], 300); // Play each note for 300ms
      delay(50);
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
}
