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
    showPiles(a, b, c);
    delay(TRANSITION_TIME_DELAY);
    showPiles(pileA, pileB, pileC);
    delay(TRANSITION_TIME_DELAY);
    setPiles(a, b, c);
}