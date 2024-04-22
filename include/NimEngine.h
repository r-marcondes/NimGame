#define NUM_PILES 3

#define PLAYER_CHOOSE_PILE 1
#define PLAYER_CHOOSE_PIECES 2
#define END_GAME 3
#define MOVE_ERROR -1

class CNimEngine
{
    private:
        int gameStatus;
        bool playerOneTurn;
        int piles[NUM_PILES];
        int chosenPile;
        bool isLastPile;
        void checkLastPile();
        bool checkEndGame();
            
    public:
        CNimEngine();
        void reset();
        int choosePile(int pile);
        int makeMove(int number_of_pieces);
        int getPile(int pile);
        int getStatus();
        char getPlayer();
        char getChosenPile();
};
