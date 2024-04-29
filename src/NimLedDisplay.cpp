#include "NimLedDisplay.h"

void CNimLedDisplay::setup()
{
  lc.shutdown(0, false); //MAX7219 wake up call
  lc.setIntensity(0, 8); //set brightness to a medium value (0 - 15)
  lc.clearDisplay(0); //turns all leds off
}

void CNimLedDisplay::showPiles(int a, int b, int c)
{
    for(int col = 0; col < 8; col++)
    {
        for(int row = 0; row < 8; row++)
        {
            if((row < 2 && col < a) || (row > 2 && row < 5 && col < b) || (row > 5 && col < c))
            {
                lc.setLed(0, row, col, true);
            }
            else
            {
                lc.setLed(0, row, col, false);
            }
        }
    }
}

void CNimLedDisplay::setPiles(int a, int b, int c)
{
    pileA = a;
    pileB = b;
    pileC = c;
    showPiles(a, b, c);
}

void CNimLedDisplay::transitionPiles(int a, int b, int c)
{
    //Sets isBlinking to true to make the removed pieces blink a couple of time before vanishing
    prevTime = millis();
    isBlinking = true;
    nextA = a;
    nextB = b;
    nextC = c;
    blinkCount = 0;
}

//This method is to be called from the main loop every cycle (so can blink without pausing the code)
//Returns true if blinking and false if not
bool CNimLedDisplay::loop()
{
    if (isBlinking)
    {        
        if(millis() - prevTime > TRANSITION_TIME_DELAY)
        {
            prevTime = millis();
            if (blinkCount == 0 || blinkCount == 2)
            {
                showPiles(nextA, nextB, nextC);
            }
            else if (blinkCount == 1 || blinkCount == 3)
            {
                showPiles(pileA, pileB, pileC);
            }
            else
            {
                setPiles(nextA, nextB, nextC);//in the last iteraction sets the new piles defenitely
                isBlinking = false;
            }
            blinkCount++;
        }
        return true;
    }
    return false;
}