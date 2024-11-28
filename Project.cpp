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

    while(exitFlag == false)
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
    myPlayer = new Player(myGM);

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
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
        int hasObject = 0;

    MacUILib_clearScreen();
    int i,j;
    for(i=0;i<myGM->getBoardSizeX()+2;i++){
        MacUILib_printf("#");
    }
    MacUILib_printf("\n");


    for(i=0;i<myGM->getBoardSizeY();i++){
            MacUILib_printf("#");
        for(j=0; j<myGM->getBoardSizeX();j++){
            if(j == (myPlayer->getPlayerPos().pos->x) && i == (myPlayer->getPlayerPos().pos->y)){
                MacUILib_printf("%c", myPlayer->getPlayerPos().getSymbol());
            }
            else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("#\n");
    }
    for(i=0;i<myGM->getBoardSizeX()+2;i++){
        MacUILib_printf("#");
    }
    MacUILib_printf("\n");
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
