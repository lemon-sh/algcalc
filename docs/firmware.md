# Firmware
Important: If you get a "programmer is not responding" error while uploading, change the board to Arduino Uno in PlatformIO
## Project structure
* The firmware for the algCalc is a [PlatformIO](https://platformio.org/) project.
* I am using Code-OSS (VSCode) for working on it, but it should work in any editor supported by PlatformIO.
* Source files are indented with a single tab, not spaces.
* C++ header files are `.hpp` and C header files are `.h`.
## External libraries used (aka, kudos to these people)
* [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal)
* [fp64lib](https://github.com/fp64lib/fp64lib)
* A custom version of [TinyExpr](https://github.com/codeplea/tinyexpr) modified to work with the fp64lib's `float64_t` type
* [Keypad](https://github.com/Chris--A/Keypad)
