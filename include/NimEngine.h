#define NUM_PILES 3

//Status
#define SELECT_MODE 1
#define SELECT_LEVEL 2
#define SELECT_WHO_STARTS 3
#define PLAYER_CHOOSE_PILE 4
#define PLAYER_CHOOSE_PIECES 5
#define END_GAME 6
#define MOVE_ERROR -1

class CNimEngine
{
    private:
        bool onePlayerMode;
        bool computerIsPlayerOne;
        int level;
        int gameStatus;
        bool playerOneTurn;
        int piles[NUM_PILES];
        int chosenPile;
        bool isLastPile;
        void checkLastPile();
        bool checkEndGame();
        int computerMakeRandomMove();
        int computerMakeBestMove();
        bool checkWinnerPosition(int a, int b, int c);
        int move(int pile, int pieces);
            
    public:
        CNimEngine();
        void reset();
        bool isOnePlayerMode();
        void setMode(bool onePlayer);
        void setLevel(int l);
        void setComputerPlayer(bool playerOne);
        int choosePile(int pile);
        int makeMove(int number_of_pieces);
        int computerMakeMove();
        int getPile(int pile);
        int getStatus();
        char getPlayer();
        char getChosenPile();
};
