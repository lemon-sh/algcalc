# Wiring
This document contains the wiring for the microcontroller (Arduino) and the external devices
### LCD
Arduino pin(s)|LCD pin(s)
---|---
5V|_Vcc_ (2), _Led+_ (15)
GND|_GND_ (1), _RW_ (5), _Led-_ (16)
A0|_RS_ (4)
A1|_Enable_ (6)
A2-A5|_D4_ (11) - _D7_ (14)
* LCD Pin 3 should be connected to the Arduino (both 5V and GND) via a potentiometer to control the contrast.
### Keyboard
###### See [Components](/docs/components.md) for more information about the mechanical keyboard module.
Arduino pins|Keyboard pins
---|---
D2-D5|_Row 0 _-_ Row 4_
D6-D10|_Col 0 _-_ Col 5_

## Arduino pinout
![Arduino NANO pinout](media/Pinout-NANO_latest.png)
