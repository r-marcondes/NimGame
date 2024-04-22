#include <LiquidCrystal_I2C.h>

class CNimLCD
{
    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
    public:
        CNimLCD(){};
        void setup();
        void initScreen();
        void showPlayer(char c);
        void input(char c);
        void requestPile();
        void requestPieces(char c);
        void pileError();
        void piecesError(char c);
        void endGame(char c);
};
