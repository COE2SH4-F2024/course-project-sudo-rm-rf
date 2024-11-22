#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '@';
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
        // PPA3 input processing logic 
        current = myFSMMode;  
         switch(input)
        {        
            
            case '.':
                myFSMMode = STOP;
                break;     
            
            case 'a':  
                myFSMMode = LEFT;
                break;

            case 'd':  
                myFSMMode = RIGHT;
                break;

            case 'w':  
                myFSMMode = UP;
                break;
            
            case 's':  
                myFSMMode = DOWN;
                break;
            
            default:
                break;
        }
        if (3 - current == myFSMMode && myFSMMode != STOP)
            {
                myFSMMode = current;  
    }        
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added