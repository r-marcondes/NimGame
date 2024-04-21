#include "LedControl.h"

//Pins
#define PIN_LEDMATRIX_DATA 10
#define PIN_LEDMATRIX_LOAD 11
#define PIN_LEDMATRIX_CLK 12
#define NUM_LED_MATRICES 1

//Delay
#define TRANSITION_TIME_DELAY 350

class CNimLedDisplay
{
    private:
        LedControl lc = LedControl(PIN_LEDMATRIX_DATA, PIN_LEDMATRIX_CLK, PIN_LEDMATRIX_LOAD, NUM_LED_MATRICES);
        int pileA;
        int pileB;
        int pileC;

    public:
        CNimLedDisplay() {};
        void setup();
        void showPiles(int a, int b, int c);
        void setPiles(int a, int b, int c);
        void transitionPiles(int a, int b, int c);
};
