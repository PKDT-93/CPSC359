# The PopSequence

## Documentation 

### Overview

In an era where digital distractions are incessantly vying for our attention, maintaining focus during study sessions has become a formidable challenge, particularly for students. The PopSequence project embodies an innovative approach to tackle this issue, leveraging the a popping balloon as a deterrent. This project is designed not merely as a punitive measure but as a tangible visualization of the time spent away from study due to phone distractions. Each lift of the phone triggers a vacuum pump, inflating a balloon attached to the setup. The growing size of the balloon serves as a real-time indicator of the accumulated distractions, culminating in a popping sound if the phone is lifted excessively.

### Inspiration

This project was motivated by the need to create a physical reminder for students to stay engaged with their studies by minimizing phone usage, by employing a negative reinforcement mechanism where the adverse consequence (the balloon popping) is introduced to decrease the undesired behavior (phone usage during study times). However, PopSequence goes a step beyond just deterrence. By visualizing the amount of time distracted in the form of a balloon's expansion, it offers a direct, tangible representation of time wasted, thus encouraging students to reflect on their habits and make conscious decisions to focus.

### How It Works

By integrating MPU-6050 accelerometer and gyroscope sensor, attached to the back of a phone, to detect when the phone is lifted. When the user presses a button, it will activate a 25 minute study window from the current time, displayed on a I2C display, where lifting up your phone will cause the motor to be activated through a L98N motor-driver controlling a vacuum pump connected to the Arduino board, initiating the inflation of the balloon, and continues until the phone is put back down. 

<hr>

### Concept Images
![Concept Image](Images/Concept.png)

### Schematic Diagram
<img src="Images/Diagram.png" style="width: 50%; height: 50%"/>​

### Final Artifact
<img src="Images/Final_Artifact.png" style="width: 50%; height: 50%"/>​

### Video
[![Musical Seashells](https://i3.ytimg.com/vi/X3xYvU7gXgk/maxresdefault.jpg)](https://youtu.be/X3xYvU7gXgk?feature=shared)

<hr>

### References
1. "Potentiometer Documentation." *SunFounder*, docs.sunfounder.com/projects/esp32-starter-kit/en/latest/arduino/basic_projects/ar_pot.html#ar-potentiometer. Accessed 10 Feb. 2024.

2. Lathoub. "Arduino BLE-MIDI Transport Library." *GitHub*, github.com/lathoub/Arduino-BLE-MIDI?tab=readme-ov-file. Accessed 13 Feb. 2024.

3. FortySevenEffects. "Arduino MIDI Library." *GitHub*, github.com/FortySevenEffects/arduino_midi_library. Accessed 13 Feb. 2024.

4. "Bluetooth MIDI Connect." *App Store*, apps.apple.com/us/app/bluetooth-midi-connect/id1074606480?mt=12. Accessed 13 Feb. 2024.

5. "GarageBand for MacOS." *Apple*, www.apple.com/ca/mac/garageband/. Accessed 12 Feb. 2024.


### Components
    - ESP32 WROOM 32E
    - Breadboard
    - Jumper Pins
    - AT42QT1070 Capacitive Touch Sensor
    - 220 OHM Resistor
    - 10-12K Resistors x4
    - Potentiometer
    - LED pins x 4
