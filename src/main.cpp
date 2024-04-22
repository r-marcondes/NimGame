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
#include "NimEngine.h"

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

//Game Engine object
CNimEngine game = CNimEngine();

void setup() 
{
  //Serial monitor for degugging
  //Serial.begin(9600);

  //LCD setup
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("**** Nim Game!! ****");
  lcd.setCursor(0, 1);
  lcd.print("PLAYER 1");
  lcd.setCursor(0, 2);
  lcd.print("Choose pile (A,B,C):");

  //Led matrix setup
  ledcntrl.setup();
  ledcntrl.setPiles(game.getPile(0), game.getPile(1), game.getPile(2));
 }

void loop() 
{
  char key_input = keypad.getKey();
  int res;
  int num_pieces;

  if(key_input)
  {
    Serial.println(key_input);
    lcd.setCursor(0, 3);
    lcd.print(key_input);

    if(game.getStatus() == PLAYER_CHOOSE_PILE)
    {
      switch (key_input)
      {
        case 'A':
          res = game.choosePile(0);
          break;
        case 'B':
          res = game.choosePile(1);
          break;
        case 'C':
          res = game.choosePile(2);
          break;
        default:
          res = MOVE_ERROR;
      }
      if(res == MOVE_ERROR)
      {
        lcd.setCursor(0, 2);
        lcd.print("Not a valid pile!   ");
        delay(1000);
        lcd.setCursor(0, 2);
        lcd.print("Choose pile (A,B,C):");
      }
      else
      {
        lcd.setCursor(0, 2);
        lcd.print("# of pieces from ");
        lcd.setCursor(17, 2);
        lcd.print(key_input);
      }
    }
    else if(game.getStatus() == PLAYER_CHOOSE_PIECES)
    {
      num_pieces = key_input - '0'; //convert char into int using ASCII table
      Serial.println(key_input);
      if(num_pieces > 0 && num_pieces <= 7)
      {
        res = game.makeMove(num_pieces);
        if(res != MOVE_ERROR)
        {
          ledcntrl.transitionPiles(game.getPile(0), game.getPile(1), game.getPile(2));
          lcd.setCursor(7, 1);
          lcd.print(game.getPlayer());
          lcd.setCursor(0, 2);
          lcd.print("Choose pile (A,B,C):");
          return;        
        }
      }
      lcd.setCursor(0, 2);
      lcd.print("Not a valid number! ");
      delay(1500);
      lcd.setCursor(0, 2);
      lcd.print("# of pieces from ");
      lcd.setCursor(17, 2);
      lcd.print(game.getChosenPile());
    }
  }
}
