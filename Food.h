#ifndef FOOD_H
#define FOOD_H

//Using cstdlib and time library for RNG
#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

class Food{
    private:
        objPosArrayList *foodBucket;
        int xRange;
        int yRange;

    public:
        Food();
        Food(int boardSizeX, int boardSizeY);
        ~Food();

        void generateFood(objPosArrayList* blockOff);
        objPosArrayList* getFoodPos();
};

#endif