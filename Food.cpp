#include "Food.h"

#include <stdlib.h>
#include <time.h>

Food::Food(GameMechs *mainGameMechs)
{
    foodPos = objPos(0, 0, '0');
    mainGameMechsRef = mainGameMechs;
    srand(time(NULL));
}

Food::~Food() 
{
    
}

// Generate food coordinate that does not overlap with any positions in the passed arrayList
void Food::generateFood(objPosArrayList &blockedList)
{
    int xCoord, yCoord, j;
    objPos current;
    int badCoord = 1;
    while(badCoord) {

        // Generate random coord
        badCoord = 0;
        xCoord = (rand() % (mainGameMechsRef->getBoardSizeX() - 2)) + 1;
        yCoord = (rand() % (mainGameMechsRef->getBoardSizeY() - 2)) + 1;

        // Check that no overlaps occured
        for(j = 0; j < blockedList.getSize(); j++) {
            blockedList.getElement(current, j);
            if(xCoord == current.x && current.y == yCoord) {
                badCoord = 1;
                j = 100;
            }
        }
    }

    objPos *temp = new objPos(xCoord, yCoord, '0');
    foodPos.setObjPos(*temp);
    delete temp;
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}