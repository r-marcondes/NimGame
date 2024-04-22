#include "NimEngine.h"

CNimEngine::CNimEngine()
{
    piles[0] = 3;
    piles[1] = 5;
    piles[2] = 7;

    playerOneTurn = true;
    gameStatus = PLAYER_CHOOSE_PILE;
}

int CNimEngine::choosePile(int pile)
{
    if (pile < NUM_PILES)
    {
        if(piles[pile] > 0)
        {
            chosenPile = pile;
            gameStatus = PLAYER_CHOOSE_PIECES;
            return PLAYER_CHOOSE_PIECES;
        }
    }
    return MOVE_ERROR;
}

int CNimEngine::makeMove(int number_of_pieces)
{
    if(piles[chosenPile] >= number_of_pieces)
    {
        piles[chosenPile] -= number_of_pieces;
        gameStatus = PLAYER_CHOOSE_PILE;
        playerOneTurn = !playerOneTurn;
        
        return PLAYER_CHOOSE_PILE;
    }

    return MOVE_ERROR;
}

int CNimEngine::getPile(int pile)
{
    return piles[pile];
}

int CNimEngine::getStatus()
{
    return gameStatus;
}

char CNimEngine::getPlayer()
{
    if(playerOneTurn)
        return '1';
    else
        return '2';
}

char CNimEngine::getChosenPile()
{
    return chosenPile + 'A'; //return ASCII code for A B or C according to chosen pile
}
