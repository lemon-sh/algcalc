// app.cpp - refer to the header file for more information

#include <Wire.h>
#include <LiquidCrystal.h>
#include <tinyexpr.h>
#include "app.hpp"

#define BUFSIZE 64 // <256
#define VERSION "0.1"

const static char inferr[] PROGMEM = "Undefined     ";
const static char nanerr[] PROGMEM = "Error at %d";

extern char *__brkval;
int freeMemory() {
  char top;
#if defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif
}

namespace App
{
	LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
	char masterbuf[BUFSIZE+1], slavebuf[17] = "                ";
	byte buflength = 0, cursoroffset = 0, viewoffset = 0;
	float64_t evalout;
	te_variable evalvar = {"x", &evalout};

	void render(byte withslave)
	{
		if (withslave)
		{
			lcd.setCursor(0, 1);
			lcd.print(slavebuf);
		}
		if (cursoroffset <= viewoffset)
		{
			viewoffset = cursoroffset - 1 >= 0 ? cursoroffset - 1 : 0;
		}
		else if (cursoroffset > viewoffset + 15)
		{
			viewoffset = cursoroffset >= 15 ? cursoroffset - 15 : 0;
		}
		byte viewlength = buflength - viewoffset;
		if (viewlength > 16)
			viewlength = 16;
		char view[17];
		memcpy(view, masterbuf + viewoffset, viewlength);
		byte padsize = 16 - viewlength;
		if (padsize)
		{
			memset(view + viewlength, ' ', padsize);
			view[viewlength + padsize] = 0;
		}
		else
		{
			view[viewlength] = 0;
		}

		lcd.setCursor(0, 0);
		lcd.print(view);
		lcd.setCursor(cursoroffset - viewoffset, 0);
	}

	void left()
	{
		if (cursoroffset - 1 >= 0) {
			cursoroffset--;
			render(0);
		}
	}

	void right()
	{
		if (cursoroffset + 1 <= buflength) {
			cursoroffset++;
			render(0);
		}
	}

	void delete_cursor() {
		if (buflength == 0 || cursoroffset == 0) return;
		for (byte i = cursoroffset; i < buflength; i++)
		{
			masterbuf[i-1] = masterbuf[i];
		}
		buflength--;
		cursoroffset--;
		render(0);
	}

	void insert_cursor(char elem) {
		if (buflength == BUFSIZE) return;
		for (byte i = buflength; i > cursoroffset; i--)
		{
			masterbuf[i] = masterbuf[i-1];
		}
		masterbuf[cursoroffset] = elem;
		buflength++;
		cursoroffset++;
		render(0);
	}

	void insert_cursor(char* elems, byte negoff) {
		unsigned int elemslen = strlen(elems);
		if (buflength+elemslen > BUFSIZE) return;
		for (byte i = buflength-1+elemslen; i > cursoroffset+elemslen; i--)
		{
			masterbuf[i] = masterbuf[i-elemslen];
		}
		memcpy(masterbuf+cursoroffset, elems, elemslen);
		buflength += elemslen;
		cursoroffset += elemslen - negoff;
		render(0);
	}

	void clearmaster() {
		buflength = cursoroffset = 0;
		render(0);
	}

	void calculate() {
		int terr;
		masterbuf[buflength] = 0;
		te_expr *expr = te_compile(masterbuf, &evalvar, 1, &terr);
		evalout = te_eval(expr);
		te_free(expr);
		slavebuf[0] = '=';
		slavebuf[1] = ' ';
		if (isnan(evalout)) {
			cursoroffset = terr-1;
			int snsize = snprintf_P(slavebuf+2, 15, nanerr, terr);
			if (snsize < 14) {
				memset(slavebuf+snsize+2, ' ', 14-snsize);				
			}
		} else if (isinf(evalout)) {
			strcpy_P(slavebuf+2, inferr);
		} else {
			strcpy(slavebuf+2, fp64_to_string(evalout, 14, 0));
		}
		render(1);
	}

	void init()
	{
		lcd.begin(16, 2);
		lcd.setCursor(1, 0);
		lcd.print(F("algCalc " VERSION));
		lcd.setCursor(1, 1);
		lcd.print(F("Adam & lemonsh"));
		delay(2000);
		lcd.cursor();
		render(1);
	}

	void input(InputType inputtype)
	{
		switch (inputtype)
		{
			case InputType::d0: insert_cursor('0'); break;
			case InputType::d1: insert_cursor('1'); break;
			case InputType::d2: insert_cursor('2'); break;
			case InputType::d3: insert_cursor('3'); break;
			case InputType::d4: insert_cursor('4'); break;
			case InputType::d5: insert_cursor('5'); break;
			case InputType::d6: insert_cursor('6'); break;
			case InputType::d7: insert_cursor('7'); break;
			case InputType::d8: insert_cursor('8'); break;
			case InputType::d9: insert_cursor('9'); break;

			case InputType::left: left(); break;
			case InputType::right: right(); break;
			case InputType::del: delete_cursor(); break;
			case InputType::ret: calculate(); break;
			case InputType::add: insert_cursor('+'); break;
			case InputType::sub: insert_cursor('-'); break;
			case InputType::mul: insert_cursor('*'); break;
			case InputType::div: insert_cursor('/'); break;
			case InputType::dot: insert_cursor('.'); break;
			case InputType::parbeg: insert_cursor('('); break;
			case InputType::parend: insert_cursor(')'); break;
			case InputType::clr: clearmaster(); break;

			case InputType::sqrt: insert_cursor("sqrt()", 0); break;
		}
	}
}