# OpenHaldex

Manual controller for Audi A3/Golf 4 Haldex differential.

## Hardware

- Arduino Uno
- TB6560
- 10kOhm linear potentiometer

Set up TB6560 module:
- Running current: 500mA
- Stop current: 50%
- 2 phase excitation
- no decay

Arduino pinout:
 - To TB6560
    - Pin 13: enable
    - Pin 12: direction
    - Pin 11: clock
 - Potentiometer:
    - put it between GND and 5V
    - connect the middle pin to A0

Connect the stepper motor:
 - Orange: A+
 - Black: A-
 - Transparent: B+
 - White: B-

 If your stepper motor has different colored wires: it is the same order as it is used for connecting to the original controller.

Optional:
 - You can use Pin 10 on the Arduino as a quick release: when connected to ground, the valve is immediately released and stays released as long as Pin 10 is connected to ground. It returns to the set position afterwards.