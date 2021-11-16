// main.cpp - Input
// ----------------
// Entry point of the firmware.
// This initializes the App and handles the serial/physical keyboard input.

#include <Arduino.h>
#include <Keypad.h>
#include "app.hpp"

const byte rows = 4;
const byte cols = 5;
char keys[rows][cols] = {
  {'7','8','9','A','B'},
  {'4','5','6','C','D'},
  {'1','2','3','E','F'},
  {'0','X','Z','G','H'}
};
byte rowPins[rows] = {2,3,4,5};
byte colPins[cols] = {6,7,8,9,10};
byte fnmode = 0;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

void setup() {
	App::init();
}

void loop() {
	char key = keypad.waitForKey();
	if (fnmode) {
		switch(key) {
			case 'E': App::input(App::InputType::parbeg); break;
			case 'F': App::input(App::InputType::parend); break;
			case 'G': App::input(App::InputType::pow); break;
			case '7': App::input(App::InputType::sqrt); break;
			case '8': App::input(App::InputType::abs); break;
			case '6': App::input(App::InputType::tan); break;
			case '5': App::input(App::InputType::cos); break;
			case '4': App::input(App::InputType::sin); break;
			case '1': App::input(App::InputType::pi); break;
			case 'B': App::input(App::InputType::clr); break;
			case '3': App::input(App::InputType::x); break;
		}
		fnmode = 0;
	} else switch(key) {
		case 'X': App::input(App::InputType::left); break;
		case 'Z': App::input(App::InputType::right); break;
		case 'A': App::input(App::InputType::del); break;
		case 'B': App::input(App::InputType::dot); break;
		case 'G': App::input(App::InputType::ret); break;
		case '0': App::input(App::InputType::d0); break;
		case '1': App::input(App::InputType::d1); break;
		case '2': App::input(App::InputType::d2); break;
		case '3': App::input(App::InputType::d3); break;
		case '4': App::input(App::InputType::d4); break;
		case '5': App::input(App::InputType::d5); break;
		case '6': App::input(App::InputType::d6); break;
		case '7': App::input(App::InputType::d7); break;
		case '8': App::input(App::InputType::d8); break;
		case '9': App::input(App::InputType::d9); break;
		case 'C': App::input(App::InputType::add); break;
		case 'D': App::input(App::InputType::sub); break;
		case 'E': App::input(App::InputType::mul); break;
		case 'F': App::input(App::InputType::div); break;
		case 'H': fnmode = 1;
	}
}