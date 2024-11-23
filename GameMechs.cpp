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

// do you need a destructor?
GameMechs::~GameMechs()
{
    //No memory to delete
}

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
objPos GameMechs::generateRandomPosition() const
{
    int x = rand() % boardSizeX;
    int y = rand() % boardSizeY;
    return objPos(x, y, 'F'); // 'F' for food
}

bool GameMechs::isPositionValid(const objPos& position, const objPosArrayList* blockOff) const
{
    for(int i = 0; i < blockOff->getSize(); ++i)
    {
        if(blockOff->getElement(i).isPosEqual(&position))
        {
            return false;
        }
    }
    return true;
}

void GameMechs::generateFood(const objPosArrayList* blockOff)
{
    do
    {
        food = generateRandomPosition();
    }while (!isPositionValid(food, blockOff));
}

objPos GameMechs::getFoodPos() const
{
    return food;
}
