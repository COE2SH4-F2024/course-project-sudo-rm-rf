#include "Food.h"

Food::Food()
{
    //Initialising food object outside of game board
    objPos foodPos;
    foodPos.setObjPos(-1, -1, 'X');
    
    //Create a new objPosArrayList on the heap
    foodBucket = new objPosArrayList();
    
    //Add foodPos to head of array list
    foodBucket->insertHead(foodPos);

    xRange = 20;
    yRange = 20;

    //Seed RNG with current time
    srand(time(NULL));
}

Food::Food(int boardSizeX, int boardSizeY)
{
    //Initialize food object outside of game board
    objPos foodPos;
    foodPos.setObjPos(-1, -1, 'X');
    
    //Create a new objPosArrayList on the heap
    foodBucket = new objPosArrayList();
    
    //Add foodPos to head of array list
    foodBucket->insertHead(foodPos);

    xRange = boardSizeX;
    yRange = boardSizeY;

    //Seed RNG with current time
    srand(time(NULL));
}

Food::~Food()
{
    //Deallocate memory from heap
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int overlap, randX, randY;

    //Object for temporary storage of playerArrayList position and foodBucket element position
    objPos tempElementPos, tempFoodPos;

    //Continuosly generate random coordinates for food
    do{
        //Reset do while loop exit flag
        overlap = 0;

        //Empty the list
        while (foodBucket->getSize() > 0) {
            foodBucket->removeTail();
        }

        int i, j;
        for (i = 0; i < 3; i++) { // 3 food objects
            objPos newFoodPos;

            //Generate random x and y coordinates located on the board
            randX = (rand() % (xRange-2))+1;
            randY = (rand() % (yRange-2))+1;

            //Special character for special food
            char foodSymbol;
            
            //Assign food objects: 1 special food item, 2 regular food items
            if(i == 0){
                foodSymbol = '$';
            }
            else{
                foodSymbol = 'X';
            }
            
            //Update food position
            newFoodPos.setObjPos(randX, randY, foodSymbol);

            //Check if other food elements have the same coordinates
            for(int foodElementIndex = 0; foodElementIndex<=i; foodElementIndex++){
                //Pass coordinates of food within food bucket
                foodBucket->getElement(foodElementIndex);

                //Flag for coordinate regeneration if coordinate overlap is detected
                if(tempFoodPos.isPosEqual(&newFoodPos)){
                    overlap = 1;
                    break;
                }
 
            }

            //Prevent adding duplicate positions to list
            if(overlap){
                break;
            }

            //Add food item to food bucket
            foodBucket->insertTail(newFoodPos);
        }
        

        //Check for overlap
        for(i = 0; i < blockOff->getSize(); i++){
            //Pass coordinates in arrayList to temporary object
            tempElementPos = blockOff->getElement(i);
            
            //Flag for overlap when food coordinates match player coordinates, regenerate coordinates
            for(j = 0; j < foodBucket->getSize(); j++){
                tempFoodPos = foodBucket->getElement(j);
                
                if (tempFoodPos.isPosEqual(&tempElementPos)) {
                    overlap = 1;
                    break;
                }
            }
            
        }


    } while(overlap);


}

objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
}