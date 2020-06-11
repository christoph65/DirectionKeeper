# DirectionKeeper
Keeps Direction of a two motor vehicle (Boat, Car) with Raspberry PI4, Ardouino Nano and CMPS14.

The Code is written in
- C++ using AtmelStudio for the Arduino Nano.
- C++ using Codeblocks and wxSmith for the Raspberry PI4

The Arduino Nano 
- has a joystick connected using the ADC for reading it and setting speed and direction (works)
- Over PWM the Arduino  is controling two RC-motors controlers for brushed motors (works)
- Gets commands over serial port from Raspberry to control the PWM (works but not integrated)

Under construction on Raspberry Pi4:
- Reading the direction using C CMPS14 over I2C Port (works)
- Having GUI with WxWidget (showing values from CMPS14 wordks and a log)
- Communication to Arduino over USB-Serial Port (next step - working on it)
- Controlalgorithm to keep direction (not started yet - this is the interesting part for my fishing boat)

My Plan is to develop the whole algorithm in 2020. 

Log
- 11.6.2020 I will check-In the first code in the next two weeks to have a backup.

