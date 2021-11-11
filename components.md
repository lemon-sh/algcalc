# Components
In order to build an algCalc device, you will need the following components:
* 2x16 LCD display with a HD44780-compatible chipset
* 5x4 matrix keypad (see below)
* Arduino Nano (or compatible) board
## Keypad
The ***g*** in al**g**Calc stands for **gaming** which is why the keypad is intended to be a matrix of **mechanical** keyboard switches (like *Cherry MX Blue*),
although you can use any kind of switch you want. The keypad should look like this (**R** is rows and **C** is columns):
![Keypad schematic](/docs/media/keypad.png)
The ["wiring"](/docs/wiring.md) page will help you connect the keypad correctly to the Arduino Nano.
## Power
The original project uses a 18650 Li-Ion cell with a TP4056 charger and a MT3608 step-up boost converter module,
although you should choose the way of powering your algCalc yourself, depending on your needs.
