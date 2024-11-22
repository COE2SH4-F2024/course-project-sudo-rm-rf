#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

//Access the player class
#include "Player.h"
#include "GameMechs.h"
using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer to instantiate a player object on the heap
GameMechs *myGM; //Global pointer to instantiate a game mechanics object on the heap
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
    myPlayer = new Player(nullptr); //PLACEHOLDER POINTER

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    MacUILib_printf("Player [x, y, sym] = [%d, %d, %c]\n" );    
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
