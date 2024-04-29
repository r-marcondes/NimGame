#include <LiquidCrystal_I2C.h>

#define MESSAGE_TIME_DELAY 1500

//Screens
#define SCREEN_MODE 1
#define SCREEN_LEVEL 2
#define SCREEN_WHO_STARTS 3
#define SCREEN_PILE 4
#define SCREEN_PIECES 5
#define SCREEN_END_GAME 6

class CNimLCD
{
    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
        long prevTime;
        bool isShowingTempMessage;
        char player;
        int nextScreen;
        char nextChar;

    public:
        CNimLCD(){};
        void setup();
        void initScreen();
        void setPlayer(char c);
        void showPlayer();
        void computerMove(int next);
        void input(char c);
        void requestMode();
        void requestLevel();
        void requestWhoStarts();
        void requestPile();
        void requestPieces(char c);
        void modeError();
        void levelError();
        void whoStartsError();
        void pileError();
        void piecesError(char c);
        void endGame();
        bool loop();
};
