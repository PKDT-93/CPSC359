# This script sends the current date-time from your computer to your arduino via serial connnection

import serial
from datetime import datetime
import time

arduino = serial.Serial(port='/dev/cu.usbmodem21401', baudrate=9600, timeout=.1)
time.sleep(2) # Wait for the serial connection to initialize

def send_datetime():
    now = datetime.now()  # Get current date and time
    time_str = now.strftime("%I:%M:%S\n")  # Add '\n' to denote end of the message
    arduino.write(bytes(time_str, 'utf-8'))  # Send over serial
    time.sleep(0.05)

while True:
    send_datetime()
    time.sleep(1)  # Update interval (1 second in this case)
