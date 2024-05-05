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
#include "NimLedDisplay.h"
#include "NimLCD.h"
#include "NimEngine.h"
#include "Buzzer.h"

//Constants
#define NUM_KEY_ROWS 4
#define NUM_KEY_COLS 4

//Pins
byte keyRowPins[NUM_KEY_ROWS] = {9, 8, 7, 6};
byte keyColPins[NUM_KEY_COLS] = {5, 4, 3, 2};
#define BUZZER_PIN 53

//Array with Keys
char keys[NUM_KEY_ROWS][NUM_KEY_COLS] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Sounds
char startGameNotes[9] = "ceg ceg";
int startGameBeats[7] = {1,1,1,1,1,1,1};
char pressKeyNotes[2] = "b";
int pressKeyBeats[1] = {1};
char moveNotes[6] = "c c g";
int moveBeats[5] = {2, 2, 2, 2, 2};
char errorNotes[4] = "d d";
int errorBeats[3] = {1, 1, 1};
char winNotes[12] = "cde def efg";
int winBeats[11] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
char looseNotes[9] = "AFGEFD C";
int looseBeats[8] = {1, 1, 1, 1, 1, 1, 2, 2};


//Components objects
Keypad keypad = Keypad(makeKeymap(keys), keyRowPins, keyColPins, NUM_KEY_ROWS, NUM_KEY_COLS);
CNimLedDisplay ledcntrl = CNimLedDisplay();
CNimLCD lcd = CNimLCD();
CBuzzer buzzer = CBuzzer(BUZZER_PIN);

//Game Engine object
CNimEngine game = CNimEngine();

//Other variables
bool computerTurn;

void setup() 
{
  //Serial monitor for degugging
  //Serial.begin(9600);

  //LCD setup
  lcd.setup();
  lcd.initScreen();
  lcd.requestMode();

  //Led matrix setup
  ledcntrl.setup();
  ledcntrl.setPiles(game.getPile(0), game.getPile(1), game.getPile(2));

  //Variables setup
  computerTurn = false;

  //Play start song
  buzzer.play(startGameNotes, startGameBeats);
}

void loop() 
{
  char key_input = keypad.getKey();
  int res;
  int num_pieces;
  int status;
  bool r1, r2;

  //Calls objects loops (for the objects that have that method)
  r1 = ledcntrl.loop();
  r2 = lcd.loop();
  buzzer.loop();
  if(r1 || r2)
  {
    return; //wait while objects have activities in their loops
  }
  
  //Checks if computers turn
  if(computerTurn)
  {
    lcd.initScreen();
    res = game.computerMakeMove();
    ledcntrl.transitionPiles(game.getPile(0), game.getPile(1), game.getPile(2));
    lcd.setPlayer(game.getPlayer());
    buzzer.play(moveNotes, moveBeats);
    if(res == END_GAME)
    {
      lcd.computerMove(SCREEN_END_GAME);
      buzzer.play(looseNotes, looseBeats);
    }
    else
    {
      lcd.computerMove(SCREEN_PILE);
    }
    computerTurn = false;
    return;
  }

  //Processes keyboard input
  if(key_input)
  {
    //Serial.println(key_input);
    lcd.input(key_input);
    buzzer.play(pressKeyNotes, pressKeyBeats);
    
    if(key_input == '*') //Entering '*' key resets the game
    {
      game.reset();
      ledcntrl.setPiles(game.getPile(0), game.getPile(1), game.getPile(2));
      lcd.initScreen();
      lcd.requestMode();
      buzzer.play(startGameNotes, startGameBeats);
      return;
    }

    status = game.getStatus();
    if(status == SELECT_MODE)
    {
      if(key_input == 'A')
      {
        game.setMode(false);
        lcd.initScreen();
        lcd.setPlayer(game.getPlayer());
        lcd.requestPile();
      }
      else if(key_input == 'B')
      {
        game.setMode(true);
        lcd.requestLevel();
      }
      else
      {
        lcd.modeError();
        buzzer.play(errorNotes, errorBeats);
      }
    }
    else if(status == SELECT_LEVEL)
    {
      if(key_input == '0' || key_input == '1' || key_input == '2')
      {
        game.setLevel(key_input - '0');
        lcd.requestWhoStarts();
      }
      else
      {
        lcd.levelError();
        buzzer.play(errorNotes, errorBeats);
      }
    }
    else if(status == SELECT_WHO_STARTS)
    {
      if(key_input == 'A') //Player starts
      {
        game.setComputerPlayer(false);
        lcd.initScreen();
        lcd.setPlayer(game.getPlayer());
        lcd.requestPile();
      }
      else if(key_input == 'B') //Computer starts
      {
        game.setComputerPlayer(true);
        computerTurn = true;
        return;
      }
      else
      {
        lcd.whoStartsError();
        buzzer.play(errorNotes, errorBeats);
      }
    }
    else if(status == PLAYER_CHOOSE_PILE)
    {
      switch(key_input)
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
        lcd.pileError();
        buzzer.play(errorNotes, errorBeats);
      }
      else
      {
        lcd.requestPieces(key_input);
      }
    }
    else if(status == PLAYER_CHOOSE_PIECES)
    {
      num_pieces = key_input - '0'; //convert char into int using ASCII table
      //Serial.println(key_input);
      if(num_pieces > 0 && num_pieces <= 7)
      {
        res = game.makeMove(num_pieces);
        if(res != MOVE_ERROR)
        {
          ledcntrl.transitionPiles(game.getPile(0), game.getPile(1), game.getPile(2));
          lcd.setPlayer(game.getPlayer());
          buzzer.play(moveNotes, moveBeats);
          if(res == END_GAME)
          {
            lcd.endGame();
            buzzer.play(winNotes, winBeats);
          }
          else
          {
            if(game.isOnePlayerMode())
            {
              computerTurn = true;
            }
            else
            {
              lcd.requestPile();
            }
          }
          return;        
        }
      }
      lcd.piecesError(game.getChosenPile());
      buzzer.play(errorNotes, errorBeats);
    }
  }
}
