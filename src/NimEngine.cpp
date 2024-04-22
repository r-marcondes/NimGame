#include "NimEngine.h"

CNimEngine::CNimEngine()
{
    reset();
}

void CNimEngine::reset()
{
    piles[0] = 3;
    piles[1] = 5;
    piles[2] = 7;

    playerOneTurn = true;
    isLastPile = false;
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

void CNimEngine::checkLastPile()
{
    int count = 0;
    for(int i = 0; i < NUM_PILES; i++)
        if(piles[i] == 0)
            count++;
    if(count > 1)
        isLastPile = true;
}

bool CNimEngine::checkEndGame()
{
    int count = 0;
    for(int i = 0; i < NUM_PILES; i++)
        count += piles[i];
    if(count == 1)
        return true;
    return false;
}

int CNimEngine::makeMove(int number_of_pieces)
{
    if((!isLastPile && piles[chosenPile] >= number_of_pieces) || (isLastPile && piles[chosenPile] > number_of_pieces))
    {
        piles[chosenPile] -= number_of_pieces;
        if (checkEndGame())
        {
            gameStatus = END_GAME;
            return END_GAME;
        }
        checkLastPile();
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
