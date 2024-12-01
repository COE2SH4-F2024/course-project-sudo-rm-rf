#include "Player.h"

#define w 119
#define a 97
#define s 115
#define d 100

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;

    //Set initial player position, player symbol to filled block
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    //Create objPosArrayList for snake body coordinates on the heap
    playerPosList = new objPosArrayList();

    //Add tempPos to the head position of the player array list
    playerPosList->insertHead(tempPos);

    currentHead = tempPos;
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;

}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos
    
    return playerPosList;

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
    //Create tempFoodList to temporarily store coordinates of food items on the board
    objPosArrayList *tempFoodList = foodRef->getFoodPos();
    
    //Element in list
    objPos tempFoodPos;

    //Update head
    updateCurrentHead();

    //Insert new current head at the head of the list
    playerPosList->insertHead(currentHead); 
    
    //Check for food collision
    int i;

    //Collision flag
    bool collided = false;
    for (i = 0; i < tempFoodList->getSize(); i++) {
        tempFoodPos = tempFoodList->getElement(i);

        // Normal food condition
        if (currentHead.isPosEqual(&tempFoodPos) && tempFoodPos.getSymbol() == 'X') {
            // Regenerate food item
            foodRef->generateFood(playerPosList);
            // Increment score by 1 for each added element
            mainGameMechsRef->incrementScore();
            collided = true;
            break;
        } 

        // Special food '$' condition (gives 10 points, no size increase)
        else if (currentHead.isPosEqual(&tempFoodPos) && tempFoodPos.getSymbol() == '$') {
            // Regenerating food item
            foodRef->generateFood(playerPosList);
            // Increment score by 5 for each special food eaten
            int j;
            for (j = 0; j < 5; j++) {
                mainGameMechsRef->incrementScore();
            }
            playerPosList->removeHead();
            collided = true;
            break;
        }

        // Special food '*' condition (gives 50 points, increases snake length)
        else if (currentHead.isPosEqual(&tempFoodPos) && tempFoodPos.getSymbol() == '*') {
            // Regenerate food item
            foodRef->generateFood(playerPosList);
            // Increment score by 100 for each '*' food eaten
            for (i=0; i < 100; i++){
                mainGameMechsRef->incrementScore();
            }
            // Increase snake length by 10
            for (i=0;i<10;i++){
                playerPosList->insertTail(playerPosList->getTailElement()); // Adds 10 new segments to the tail of the snake
            }
            collided = true;
            break;
        }
    }

    // Remove tail only when there's no collision
    if (!collided){
        playerPosList->removeTail();
    }

    // Check if there was self-collision
    if(checkSelfCollision()){
        // Setting both exit and lose flag true when self collision is true
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}

// More methods to be added
void Player::updateCurrentHead()
{
    // PPA3 Finite State Machine logic

    // update our private head variable
    currentHead = playerPosList->getHeadElement(); 

    // local method vars.
    //COL_SIZE is the max number of columns in gameboard
    //ROW_SIZE is max number of rows in gameboard
    int col_size = mainGameMechsRef->getBoardSizeY();
    int row_size = mainGameMechsRef->getBoardSizeX();

    //Switch statement to move player based on current direction
    switch(myDir){
        case UP:
            //Subtracting y position by 1 to move player object up by one
            currentHead.pos->y--;
            
            //If statement to check if player reaches top of the game board
            if(currentHead.pos->y == 0){
                currentHead.pos->y = col_size-2;
            }

            break;

        case DOWN:
            //Incrementing y position by 1 to player down by 1 row
            currentHead.pos->y++;

            //If statement to check if player reaches bottom of the game board
            if (currentHead.pos->y == col_size-1){
                currentHead.pos->y = 1;
            }

            break;

        case LEFT:

            //Decreasing x position of head element by one to the left
            currentHead.pos->x--;

            //If statement to check if player reaches the left border of game board
            if (currentHead.pos->x == 0){
                currentHead.pos->x = row_size-2;
            }

            break;

        case RIGHT:

            //Incrementing x position of head element by one to the right
            currentHead.pos->x++;

            //If statement to check if player reaches the right border of game board
            if (currentHead.pos->x == row_size-1){
                currentHead.pos->x = 1;
            }

            break;
    }
}

bool Player::checkSelfCollision()
{
    //Local objects
    objPos headElement, bodyElement;

    //Pass new head element's coordinates to local object
    headElement = playerPosList->getHeadElement();

    //Iterate through each element in playerPosList except the head element
    for(int i=1; i<playerPosList->getSize(); i++){
        //Pass element's coordinates to local object
        bodyElement = playerPosList->getElement(i);
        //Check if head collided with snake body
        if(headElement.isPosEqual(&bodyElement)){
            return true;
        }
    }

    //No collision detected otherwise
    return false;
}