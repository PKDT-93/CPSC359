### Instant Twinkle Project

This "Instant Twinkle" arduino project is a combination of using technology to make something whimsical, aimed at being a toy that delivers "instant gratification" at the push of a button. This innocent and harmless concept brings joy through simple interaction. An ESP32 Arduino device serves as the microcontroller for this interaction. When the button is pressed, a passive buzzer oscillates frequencies to the tune of "Twinkle Twinkle Little Star". Simultaneously, a yellow LED, connected to the circuit with a 250 ohm resistor, flashes in sync with each oscillation, aiming to resemble a miniature visual spectacle.

A key aesthetic feature of this project is the yellow LED, which is covered with a dark blue pen cap, punctured with four holes arranged in a crosshair pattern. This diffusion method is designed to soften and spread the LED’s light, making it less intense and akin to a dimly lit window at night. This is to resemble a dim star-like glow, which is to be appealing in low-light environments, such as during night time. 

This project is primarily targeted towards babies or children in their cribs. It serves as a device to entertain them when they are bored or in need of a soothing activity. The design is infant-friendly, requiring only a simple press of a single button to activate. This button is also enhanced with a yellow cap, which adds a feeling of friendliness and visual appeal to the device, with the intension of making it more engaging for children. The duration of each oscillation is intentionally kept brief, which encourages repeated interaction and frequent button presses, without having to wait too long. 

The assembly involves standard components easily found in an electronics hobbyist's kit. Besides the ESP32, the project utilizes a breadboard, jumper wires, a passive buzzer, and a push button. The choice of a passive buzzer allows for versatile customization as we can specify what frequency to oscillate. In this case, the oscillation frequencies were programmed to mimic "Twinkle Twinkle Little Star". The oscillation frequencies were generated with the assistance of ChatGPT, thereby streamlining the development process and reducing time spent on trial and error.

For demonstration purposes, the prototype was constructed without a resistor to allow the audience to clearly hear the buzzer's oscillations. However, in a more practical and user-friendly setting, especially when intended for young children, the use of a 250-470 Ohm resistor is recommended. This precaution ensures that the sound level is kept within a safe range.


### References
    - https://docs.sunfounder.com/projects/esp32-starter-kit/en/latest/arduino/basic_projects/ar_ac_buz.html were used to control the buzzer

    - https://chat.openai.com/ used to generate "Twinkle Twinkle Little Star" frequencies

### Components
    - ESP32 WROOM 32E
    - Breadboard
    - Jumper Pins
    - Yellow (595nm) LED
    - NPN-Transistor
    - Passive Buzzer 12mm
    - 220Ω Resistor x 2
    - 1kΩ Resistor
    - Push Button
  
