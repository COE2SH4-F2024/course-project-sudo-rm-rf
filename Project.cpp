#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

#define ESC 27

Player *myPlayer; //Global pointer to instantiate a player object on the heap
GameMechs *myGM; //Global pointer to instantiate a game mechanics object on the heap
Food *foodObj; //Global pointer to instantiate a food object on the heap

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(); 
    foodObj = new Food(myGM->getBoardSizeX(), myGM->getBoardSizeY());
    myPlayer = new Player(myGM, foodObj);

    objPosArrayList* tempPosList;

    tempPosList = myPlayer->getPlayerPos();

    //Initialize food coordinates
    foodObj->generateFood(tempPosList);

    exitFlag = false;
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
        myGM->setInput(input);
    }
}

void RunLogic(void)
{
    //Check if exit key was pressed
    if(myGM->getInput() == ESC){
        myGM->setExitTrue();
    }

    //Process player movement keys
    else{
        //Update player direction
        myPlayer->updatePlayerDir();
        //Move player based on input
        myPlayer->movePlayer();
    }

    myGM->clearInput(); //Reset input
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    //Flag for completed drawing
    bool frameFinished; 

    //Gameboard size
    int totalRows = myGM->getBoardSizeY();
    int totalCols = myGM->getBoardSizeX();

    //Initialize objects to store playerPositionList and its elements
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    //Store coordinates of food items on the board and the element
    objPosArrayList *tempFoodList = foodObj->getFoodPos();
    objPos tempFoodPos;

    //Iterate through each coordinate
    for(int row = 0; row < totalRows; row++){
        for(int col = 0; col < totalCols; col++){
          
            //Resetting frameFinished flag to false
            frameFinished = false;

            //Draw each element in player array list
            for(int index = 0; index<playerBody->getSize(); index++){
            
                tempBody = playerBody->getElement(index);

                if(tempBody.pos->x == col && tempBody.pos->y == row){
                    MacUILib_printf("%c", tempBody.symbol);
                    frameFinished = true;
                    break;
                }
            }

            //Draw each item in food array list
            if (!frameFinished) {
                for(int index=0; index<tempFoodList->getSize(); index++){
                
                    //Pass element's coordinates of food array list
                    tempFoodPos = tempFoodList->getElement(index);

                    //Print food character if applicable
                    if(tempFoodPos.pos->x == col && tempFoodPos.pos->y == row){
                        MacUILib_printf("%c", tempFoodPos.symbol);
                        frameFinished = true;
                        break;
                    }
                }
            }

            //Skip logic below so player body is not overwritten by spaces
            if(frameFinished){
                continue;
            }

            //Draw border
            if(col == 0 || col == totalCols - 1 || row == 0 || row == totalRows - 1){
                //Go to next row if the last column is reached
                if(col == totalCols - 1){
                    MacUILib_printf("#\n");
                }
                else{
                    MacUILib_printf("#");
                }
            }
            //Draw space if not the border
            else{
                MacUILib_printf(" ");
            }  
        }
    }

    MacUILib_printf("Score: %d \n", myGM->getScore());

    //Debug UI
    MacUILib_printf("==== DEBUG MESSAGES ====\n");
    MacUILib_printf("Player Positions:\n");
    for (int l = 0; l < playerBody->getSize(); l++)
    {
        tempBody = playerBody->getElement(l);
        MacUILib_printf("[%d, %d] ", tempBody.pos->x, tempBody.pos->y);
    }
    MacUILib_printf("\nBoard Size: %dx%d", myGM->getBoardSizeX(), myGM->getBoardSizeY());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 

    delete myPlayer;   
    delete myGM;

    MacUILib_uninit();
}
