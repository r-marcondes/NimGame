#include "NimLCD.h"
#include <Arduino.h>

void CNimLCD::setup()
{
    lcd.init(); 
    lcd.backlight();
    isShowingTempMessage = false;
}

void CNimLCD::initScreen()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**** Nim Game!! ****");
}

void CNimLCD::setPlayer(char c)
{
    player = c;
}

void CNimLCD::showPlayer()
{
    lcd.setCursor(0, 1);
    if(player == 'C')
    {
        lcd.print("COMPUTER");
    }
    else
    {
        lcd.print("PLAYER ");
        lcd.setCursor(7, 1);
        lcd.print(player);
    }
    lcd.setCursor(8, 1);
    lcd.print("'s TURN");
}

void CNimLCD::computerMove(int next)
{
    lcd.setCursor(0, 1);
    lcd.print("COMPUTER's TURN");
    nextScreen = next;
    isShowingTempMessage = true;
    prevTime = millis();    
}

void CNimLCD::input(char c)
{
    lcd.setCursor(0, 3);
    lcd.print(c);    
}

void CNimLCD::requestMode()
{
    initScreen();
    lcd.setCursor(0, 1);
    lcd.print("A -> 2 players game");
    lcd.setCursor(0, 2);
    lcd.print("B -> vs computer");
    lcd.setCursor(0, 3);
    lcd.print(" ");
}

void CNimLCD::requestLevel()
{
    initScreen();
    lcd.setCursor(0, 1);
    lcd.print("Select level (0-Easy");
    lcd.setCursor(0, 2);
    lcd.print("1-Medium 2-Hard):");
    lcd.setCursor(0, 3);
    lcd.print(" ");
}

void CNimLCD::requestWhoStarts()
{
    initScreen();
    lcd.setCursor(0, 1);
    lcd.print("A -> You start");
    lcd.setCursor(0, 2);
    lcd.print("B -> I start");
    lcd.setCursor(0, 3);
    lcd.print(" ");
}

void CNimLCD::requestPile()
{
    showPlayer();
    lcd.setCursor(0, 2);
    lcd.print("Choose pile (A,B,C):");
    lcd.setCursor(0, 3);
    lcd.print(" ");
}

void CNimLCD::requestPieces(char c)
{
    lcd.setCursor(0, 2);
    lcd.print("# of pieces from ");
    lcd.setCursor(17, 2);
    lcd.print(c);
    lcd.setCursor(18, 2);
    lcd.print(": ");
    lcd.setCursor(0, 3);
    lcd.print(" ");
}

void CNimLCD::pileError()
{
    lcd.setCursor(0, 2);
    lcd.print("Not a valid pile!   ");
    nextScreen = SCREEN_PILE;
    isShowingTempMessage = true;
    prevTime = millis();
}

void CNimLCD::modeError()
{
    initScreen();
    lcd.setCursor(0, 2);
    lcd.print("Invalid selection!");
    nextScreen = SCREEN_MODE;
    isShowingTempMessage = true;
    prevTime = millis();
}

void CNimLCD::levelError()
{
    initScreen();
    lcd.setCursor(0, 2);
    lcd.print("Invalid level!");
    nextScreen = SCREEN_LEVEL;
    isShowingTempMessage = true;
    prevTime = millis();
}

void CNimLCD::whoStartsError()
{
    initScreen();
    lcd.setCursor(0, 2);
    lcd.print("Invalid selection!");
    nextScreen = SCREEN_WHO_STARTS;
    isShowingTempMessage = true;
    prevTime = millis();
}

void CNimLCD::piecesError(char c)
{
    lcd.setCursor(0, 2);
    lcd.print("Not a valid number! ");
    nextScreen = SCREEN_PIECES;
    nextChar = c;
    isShowingTempMessage = true;
    prevTime = millis();
}

void CNimLCD::endGame()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**** Nim Game!! ****");
    showPlayer();
    lcd.setCursor(8, 1);
    lcd.print(" WINS !!    ");
    lcd.setCursor(0, 2);
    lcd.print("Press * to restart:");
}

bool CNimLCD::loop()
{
    if(isShowingTempMessage)
    {
        if(millis() - prevTime > MESSAGE_TIME_DELAY)
        {
            isShowingTempMessage = false;
            switch(nextScreen)
            {
                case SCREEN_MODE:
                    requestMode();
                    break;
                case SCREEN_LEVEL:
                    requestLevel();
                    break;
                case SCREEN_WHO_STARTS:
                    requestWhoStarts();
                    break;
                case SCREEN_PILE:
                    requestPile();
                    break;
                case SCREEN_PIECES:
                    requestPieces(nextChar);
                    break;
                case SCREEN_END_GAME:
                    endGame();
                    break;
            }
        }
        return true;
    }
    return false;
}