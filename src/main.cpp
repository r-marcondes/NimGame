/*
Nim game for Arduino
by Ricardo Marcondes - 2024

Components:
 - 4x4 matrix membrane keypad,
 - LCD2004 Display with  I2C backpack,
 - 8x8 dot matrix led with MAX7219 control,
 - buzzer

Libraries:
 - Keypad by Mark Stanley, Alexander Brevig
 - LiquidCrystal_I2C by Frank de Brabander
 - LedControl by Eberhard Fahle
*/

#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include "LedControl.h"

//Constants
#define NUM_KEY_ROWS 4
#define NUM_KEY_COLS 4

//Pins
byte keyRowPins[NUM_KEY_ROWS] = {9, 8, 7, 6};
byte keyColPins[NUM_KEY_COLS] = {5, 4, 3, 2};
#define PIN_LEDMATRIX_DATA 10
#define PIN_LEDMATRIX_LOAD 11
#define PIN_LEDMATRIX_CLK 12
#define NUM_LED_MATRICES 1

//Array with Keys
char keys[NUM_KEY_ROWS][NUM_KEY_COLS] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Components objects
Keypad keypad = Keypad(makeKeymap(keys), keyRowPins, keyColPins, NUM_KEY_ROWS, NUM_KEY_COLS);
LiquidCrystal_I2C lcd(0x27, 20, 4);
LedControl ledcntrl = LedControl(PIN_LEDMATRIX_DATA, PIN_LEDMATRIX_CLK, PIN_LEDMATRIX_LOAD, NUM_LED_MATRICES);

void setup() 
{
  //Serial.begin(9600);
  //LCD setup
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("**** Nim Game!! ****");

  //Led matrix setup
  ledcntrl.shutdown(0, false); //MAX7219 wake up call
  ledcntrl.setIntensity(0, 8); //set brightness to a medium value (0 - 15)
  ledcntrl.clearDisplay(0); //turns all leds off

  byte a[5]={B01111110,B10001000,B10001000,B10001000,B01111110};
  ledcntrl.setRow(0,0,a[0]);
  ledcntrl.setRow(0,1,a[1]);
  ledcntrl.setRow(0,2,a[2]);
  ledcntrl.setRow(0,3,a[3]);
  ledcntrl.setRow(0,4,a[4]);
}

void loop() 
{
  char key_input = keypad.getKey();

  if (key_input)
  {
    //Serial.println(key_input);
    lcd.setCursor(0, 1);
    lcd.print(key_input);
  }
}
