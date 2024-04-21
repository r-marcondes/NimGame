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
*/

#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//Constants
const byte NUM_KEY_ROWS = 4;
const byte NUM_KEY_COLS = 4;

//Array with Keys
char keys[NUM_KEY_ROWS][NUM_KEY_COLS] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Pins
byte keyRowPins[NUM_KEY_ROWS] = {9, 8, 7, 6};
byte keyColPins[NUM_KEY_COLS] = {5, 4, 3, 2};

//Components objects
Keypad keypad = Keypad(makeKeymap(keys), keyRowPins, keyColPins, NUM_KEY_ROWS, NUM_KEY_COLS);
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() 
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Ricardo Marcondes");
  lcd.setCursor(0,2);
  lcd.print("abcd - ABCD - 012345");
  lcd.setCursor(0,3);
  lcd.print("**** Nim Game!! ****");
}

void loop() 
{
  char key_input = keypad.getKey();

  if (key_input)
  {
    Serial.println(key_input);
  }
}
