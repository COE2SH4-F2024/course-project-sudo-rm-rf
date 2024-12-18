#include "GameMechs.h"
#include "MacUILib.h"

//Time library for random seed
#include <time.h>

GameMechs::GameMechs()
{
    input = ' ';
    score = 0;
    exitFlag = false;
    loseFlag = false;

    boardSizeX = 20;
    boardSizeY = 10;

    //Random seed
    srand(time(NULL));
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = ' ';
    score = 0;
    exitFlag = false;
    loseFlag = false;

    boardSizeX = boardX;
    boardSizeY = boardY;

    //Random seed
    srand(time(NULL));
}

//Do not need a destructor since there is nothing on the heap to delete

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() 
{
    if (MacUILib_hasChar())
    {  
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = ' ';
}

// More methods should be added here
