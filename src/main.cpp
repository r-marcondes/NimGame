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
#include "NimLedDisplay.h"

//Constants
#define NUM_KEY_ROWS 4
#define NUM_KEY_COLS 4

//Pins
byte keyRowPins[NUM_KEY_ROWS] = {9, 8, 7, 6};
byte keyColPins[NUM_KEY_COLS] = {5, 4, 3, 2};

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
CNimLedDisplay ledcntrl = CNimLedDisplay();

void setup() 
{
  //Serial.begin(9600);
  //LCD setup
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("**** Nim Game!! ****");

  //Led matrix setup
  ledcntrl.setup();
  ledcntrl.setPiles (3, 5, 7);
 }

void loop() 
{
  char key_input = keypad.getKey();

  if(key_input)
  {
    //Serial.println(key_input);
    lcd.setCursor(0, 1);
    lcd.print(key_input);
    if(key_input == '1')
    {
      ledcntrl.transitionPiles(3, 5, 5);
    }
  }
}
