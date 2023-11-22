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

void Food::generateFood(objPosArrayList blockedList)
{
    int xCoord, yCoord, j;
    objPos current;
    int badCoord = 1;
    while(badCoord) {
        badCoord = 0;
        xCoord = (rand() % mainGameMechsRef->getBoardSizeX()) + 1;
        yCoord = (rand() % mainGameMechsRef->getBoardSizeY()) + 1;

        for(j = 0; j < blockedList.getSize(); j++) {
            blockedList.getElement(current, j);
            if(xCoord == current.x && current.y == yCoord) {
                badCoord = 1;
                j = 100;
            }
        }
    }
    foodPos.setObjPos(objPos(xCoord, yCoord, foodPos.getSymbol()));
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}