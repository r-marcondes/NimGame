#include "NimEngine.h"
#include <Arduino.h>

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
    gameStatus = SELECT_MODE;
}

bool CNimEngine::isOnePlayerMode()
{
    return onePlayerMode;
}

void CNimEngine::setMode(bool onePlayer)
{
    onePlayerMode = onePlayer;
    if (onePlayer)
    {
        gameStatus = SELECT_LEVEL;
    }
    else
    {
        gameStatus = PLAYER_CHOOSE_PILE;
    }
}

void CNimEngine::setLevel(int l)
{
    level = l;
    gameStatus = SELECT_WHO_STARTS;
}

void CNimEngine::setComputerPlayer(bool playerOne)
{
    computerIsPlayerOne = playerOne;
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

int CNimEngine::move(int pile, int pieces)
{
    piles[pile] -= pieces;
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

int CNimEngine::makeMove(int number_of_pieces)
{
    if((!isLastPile && piles[chosenPile] >= number_of_pieces) || (isLastPile && piles[chosenPile] > number_of_pieces))
    {
        return move(chosenPile, number_of_pieces);
    }

    return MOVE_ERROR;
}

int CNimEngine::computerMakeRandomMove()
{
    int randomPile, randomPieces;
    do
    {
        randomPile = random(3);
    } while (piles[randomPile] == 0);

    if(!isLastPile)
    {
        randomPieces = random(piles[randomPile]) + 1;
    }
    else
    {
        randomPieces = random(piles[randomPile] - 1) + 1;        
    }
    
    return move(randomPile, randomPieces);
}

bool CNimEngine::checkWinnerPosition(int a, int b, int c)
{
    bool winner;
    if((a + b + c) == 1 ) //If your opponent is left with only one piece, you win
    {
        winner = true;
    }
    else if((a == 1) && (b == 1) && (c == 1)) //1 1 1 is a winning position
    {
        winner = true;
    }
    else if((a + b + c) == 2) //1 1 is a loosing position (exception to the XOR rule below)
    {
        winner = false;
    }
    else if((a ^ b ^ c) == 0) //if a XOR b XOR c is 0, it's a winning position
    {
        winner = true;
    }
    else //anything else is loosing
    {
        winner = false;
    }
    return winner;
}

int CNimEngine::computerMakeBestMove()
{
    int i, j;
    bool win;

    if(checkWinnerPosition(piles[0], piles[1], piles[2]))
    {
        //No way to perform winning move -> takes 1 piece from random pile
        int randomPile;
        do
        {
            randomPile = random(3);
        } while (piles[randomPile] == 0);
        
        return move(randomPile, 1);        
    }
    else
    {
        for(i = 0; i < NUM_PILES; i++)
        {
            for(j = 1; j <= piles[i]; j++)
            {
                if(i == 0)
                {
                    win = checkWinnerPosition(piles[0] - j, piles[1], piles[2]);
                }
                else if(i == 1)
                {
                    win = checkWinnerPosition(piles[0], piles[1] - j, piles[2]);
                }
                else
                {
                    win = checkWinnerPosition(piles[0], piles[1], piles[2] - j);
                }
                if(win)
                {
                    return move(i, j);
                }
            }
        }
    }
}

int CNimEngine::computerMakeMove()
{
    if(level == 2) //Always plays best move
    {
        return computerMakeBestMove();
    }
    else if(level == 1) //Plays randomly at the begging, but best moves at the end game
    {
        if((piles[0] + piles[1] + piles[2]) < 6)
        {
            return computerMakeBestMove();
        }
        else
        {
            return computerMakeRandomMove();
        }
    }
    return computerMakeRandomMove(); //At level 0 all moves are random
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
    if(onePlayerMode && ((computerIsPlayerOne && playerOneTurn) || (!computerIsPlayerOne && !playerOneTurn)))
    {
        return 'C';
    }
    else
    {
        if(playerOneTurn)
            return '1';
        else
            return '2';
    }
}

char CNimEngine::getChosenPile()
{
    return chosenPile + 'A'; //return ASCII code for A B or C according to chosen pile
}
