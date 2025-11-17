
# Interfacing RTC Module with Raspberry Pi Pico

DS3231 real-time clock with the Raspberry Pi Pico, which includes connecting via I²C, managing an LCD screen, and using firmware based on Arduino.


## Project Overview
This project reads the current date, time, and temperature from the DS3231 real-time clock module and shows the information on a 20×4 I²C LCD connected to the Raspberry Pi Pico. It demonstrates how the Pico can communicate with several I²C devices at once, handle real-time data using the DS3231, and display the results in a clear and easy-to-read way through the Arduino framework. The code is built to be straightforward, dependable, and easy to update, making it a great choice for both new users and those working on more complex time-related projects.

## Features
- Reads real-time date, time, and temperature from the DS3231 RTC
- Displays formatted output on a 20×4 I²C LCD
- Uses a shared I²C bus for both the RTC and LCD
- Supports automatic or manual time setting via Arduino code

## Hardware Requirements

- Raspberry Pi Pico
- DS3231 RTC Module
- 20×4 I²C LCD Display
- Jumper Wires
- CR2032 Battery
- Breadboard (optional)
## Circuit Connection

| Pico Pin | DS3231 | LCD (I²C) |
| -------- | ------ | --------- |
| 3.3V     | VCC    | VCC       |
| GND      | GND    | GND       |
| GP4      | SDA    | SDA       |
| GP5      | SCL    | SCL       |



<p align="center">
    <img src="Images/rtc_with_pico_wiring_diagram.png" width="400">
    <p align="center">Breadboard Connection</p>
  </a>
</p>

## Libraries Required

Install via Arduino Library Manager:

- RTClib <a href="https://github.com/adafruit/RTClib.git" target="_blank">(Github)</a>
- LiquidCrystal_I2C <a href="https://github.com/johnrickman/LiquidCrystal_I2C.git" target="_blank">(Github)</a>

## Troubleshooting

1. RTC not keeping time after power-off
- CR2032 battery is missing, drained, or not making proper contact.
2. LCD shows random or unreadable characters
- Wrong I²C address (commonly 0x27 or 0x3F).
- Contrast potentiometer on LCD backpack needs adjustment.
3. RTC not detected on I²C scan
- SDA/SCL wiring incorrect or loose.
- Using 5V pull-ups on a Pico (must use 3.3V).
4. Time drifting noticeably
- Likely a low-quality DS3231 clone.
- Weak backup battery causing unstable oscillator operation
## License

[MIT](https://choosealicense.com/licenses/mit/)

