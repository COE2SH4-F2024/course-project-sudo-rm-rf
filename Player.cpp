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
    // PPA3 Finite myDir Machine logic
    // Get the current head position
    objPos head = snakeBody.getHeadElement();

    //Calculate the new head position based on the current direction
    switch(myDir)
    {
        case LEFT:
            head.pos->x -= 1;
            break;
        case RIGHT:
            head.pos->x += 1;
            break;
        case UP:
            head.pos->y -= 1;
            break;
        case DOWN:
            head.pos->y += 1;
            break;
        default:
            break;
    }

    //Insert the new head position at the head of the snake body
    snakeBody.insertHead(head);

    //Remove the tail position to simulate movement
    snakeBody.removeTail();

    //Border wraparound
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    if(head.pos->x < 0){
        head.pos->x = boardSizeX - 1;
    }
    else if(head.pos->x >= boardSizeX){
        head.pos->x = 0;
    }
    if(head.pos->y < 0){
        head.pos->y = boardSizeY - 1;
    }
    else if(head.pos->y >= boardSizeY){
        head.pos->y = 0;
    }
}

// More methods to be added
const objPosArrayList& Player::getSnakeBody() const
{
    return snakeBody;
}