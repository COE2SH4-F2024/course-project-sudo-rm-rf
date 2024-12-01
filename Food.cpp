#include "Food.h"

Food::Food()
{
    // Initializing food object outside of the game board
    objPos foodPos;
    foodPos.setObjPos(-1, -1, 'X');
    
    // Create a new objPosArrayList on the heap
    foodBucket = new objPosArrayList();
    
    // Add foodPos to head of the array list
    foodBucket->insertHead(foodPos);

    xRange = 20;
    yRange = 20;

    // Seed RNG with current time
    srand(time(NULL));
}

Food::Food(int boardSizeX, int boardSizeY)
{
    // Initialize food object outside of the game board
    objPos foodPos;
    foodPos.setObjPos(-1, -1, 'X');
    
    // Create a new objPosArrayList on the heap
    foodBucket = new objPosArrayList();
    
    // Add foodPos to head of the array list
    foodBucket->insertHead(foodPos);

    xRange = boardSizeX;
    yRange = boardSizeY;

    // Seed RNG with current time
    srand(time(NULL));
}

Food::~Food()
{
    // Deallocate memory from heap
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int overlap, randX, randY;

    // Object for temporary storage of playerArrayList position and foodBucket element position
    objPos tempElementPos, tempFoodPos;

    // Continuously generate random coordinates for food
    do {
        // Reset do while loop exit flag
        overlap = 0;

        // Empty the list
        while (foodBucket->getSize() > 0) {
            foodBucket->removeTail();
        }

        // Generate 5 food items, 3 normal and 2 special
        int i, j;
        for (i = 0; i < 5; i++) { // Generate 5 food items
            objPos newFoodPos;

            // Generate random x and y coordinates located on the board
            randX = (rand() % (xRange - 2)) + 1;
            randY = (rand() % (yRange - 2)) + 1;

            // Special character for special food
            char foodSymbol;

            if (i < 3) { // The first 3 are always normal food
                foodSymbol = 'X'; // Normal food symbol
            }
            else {
                // The remaining 2 are special food
                if (rand() % 2 == 0) {
                    foodSymbol = '$'; // Special food with 10 points, no snake length increase
                }
                else {
                    foodSymbol = '*'; // Special food with 50 points, increases snake length by 10
                }
            }

            // Update food position
            newFoodPos.setObjPos(randX, randY, foodSymbol);

            // Check if other food elements have the same coordinates
            for (int foodElementIndex = 0; foodElementIndex <= i; foodElementIndex++) {
                // Pass coordinates of food within food bucket
                foodBucket->getElement(foodElementIndex);

                // Flag for coordinate regeneration if coordinate overlap is detected
                if (tempFoodPos.isPosEqual(&newFoodPos)) {
                    overlap = 1;
                    break;
                }
            }

            // Prevent adding duplicate positions to list
            if (overlap) {
                break;
            }

            // Add food item to food bucket
            foodBucket->insertTail(newFoodPos);
        }

        // Check for overlap with player positions
        for (i = 0; i < blockOff->getSize(); i++) {
            // Pass coordinates in arrayList to temporary object
            tempElementPos = blockOff->getElement(i);
            
            // Flag for overlap when food coordinates match player coordinates, regenerate coordinates
            for (j = 0; j < foodBucket->getSize(); j++) {
                tempFoodPos = foodBucket->getElement(j);
                
                if (tempFoodPos.isPosEqual(&tempElementPos)) {
                    overlap = 1;
                    break;
                }
            }
        }

    } while (overlap);
}

objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
}
