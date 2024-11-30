#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {LEFT, DOWN, UP, RIGHT, STOP};  // This is the direction state
        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here
        bool checkSelfCollision();

    private:    
        enum Dir myDir;
        objPosArrayList *playerPosList; //Array to store snake body positions

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        //Reference for food class
        Food* foodRef;

        void updateCurrentHead();
        objPos currentHead;
};

#endif