#include "Player.h"

#define w 119
#define a 97
#define s 115
#define d 100

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '@';

    snakeBody.insertTail(playerPos);
}


Player::~Player()
{
    // delete any heap members here
    

}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos
    
    return playerPos;

}

void Player::updatePlayerDir()
{       
    char input = mainGameMechsRef->getInput();
    if(input != 0)  // if not null character
    {
        switch(input)
        {                         
            case w:
                if(myDir == STOP || myDir == LEFT || myDir == RIGHT){
                    myDir = UP;
                }
                break;
            case a:
                if(myDir == STOP || myDir == UP || myDir == DOWN){
                    myDir = LEFT;
                }
                break;
            case s:
                if(myDir == STOP || myDir == LEFT || myDir == RIGHT){
                    myDir = DOWN;
                }
                break;
            case d:
                if(myDir == STOP || myDir == UP || myDir == DOWN){
                    myDir = RIGHT;
                }
                break;
            default:
                break;
        }
        mainGameMechsRef->clearInput(); // Clear the input buffer
    }    
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    if(myDir != STOP){
        switch(myDir){
            case UP:
                if(playerPos.pos->y == 0)
                    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 1;
                else
                    playerPos.pos->y--;
                break;
            case DOWN:
                if(playerPos.pos->y == mainGameMechsRef->getBoardSizeY() - 1)
                    playerPos.pos->y = 0;
                else
                    playerPos.pos->y++;
                break;
            case LEFT:
                if(playerPos.pos->x == 0)
                    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 1;
                else
                    playerPos.pos->x--;
                break;
            case RIGHT:
                if(playerPos.pos->x == mainGameMechsRef->getBoardSizeX() - 1)
                    playerPos.pos->x = 0;
                else
                    playerPos.pos->x++;
                break;
        }
    }
}

// More methods to be added
const objPosArrayList& Player::getSnakeBody() const
{
    return snakeBody;
}