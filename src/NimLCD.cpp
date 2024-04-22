#include "NimLCD.h"
#include <Arduino.h>

void CNimLCD::setup()
{
    lcd.init(); 
    lcd.backlight();
}

void CNimLCD::initScreen()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**** Nim Game!! ****");
    showPlayer('1');
    requestPile();
}

void CNimLCD::showPlayer(char c)
{
    lcd.setCursor(0, 1);
    lcd.print("PLAYER ");
    lcd.setCursor(7, 1);
    lcd.print(c);
}

void CNimLCD::input(char c)
{
    lcd.setCursor(0, 3);
    lcd.print(c);    
}

void CNimLCD::requestPile()
{
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
    delay(1500);
    requestPile();
}

void CNimLCD::piecesError(char c)
{
    lcd.setCursor(0, 2);
    lcd.print("Not a valid number! ");
    delay(1500);
    requestPieces(c);
}

void CNimLCD::endGame(char c)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**** Nim Game!! ****");
    showPlayer(c);
    lcd.setCursor(9, 1);
    lcd.print("WINS !!");
    lcd.setCursor(0, 2);
    lcd.print("Press * to restart:");
}