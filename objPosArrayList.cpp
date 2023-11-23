#include "objPosArrayList.h"
#include <stdexcept>

// #define NULL 0

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    aList = NULL;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::increaseHeapSize()
{
        
    int i;
    objPos *temp = new objPos[sizeArray];
    for(i = 0; i < sizeArray; i++) {
        temp[i] = aList[i];
    }

    sizeArray += 10;

    delete[] aList;
    aList = new objPos[sizeArray];
    for(i = 0; i < sizeArray - 10; i++) {
        aList[i] = temp[i];
    }

    delete[] temp;
    temp = NULL;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    int i;
    for(i = sizeList; i > 0; i--) {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;
    sizeList++;
    if(sizeList == sizeArray) increaseHeapSize();
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[sizeList] = thisPos;
    sizeList++;
    if(sizeList == sizeArray) increaseHeapSize();

}

void objPosArrayList::removeHead()
{
    int i;
    for(i = 0; i < sizeList - 1; i++) {
        aList[i] = aList[i + 1];
    }

    sizeList--;
}

void objPosArrayList::removeTail()
{
    aList[sizeList - 1] = objPos(0, 0, 0);
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(index >= sizeArray) throw std::out_of_range("Invalid Index.");
    // printf("x and y (real): %d, %d\n", aList[index].x, aList[index].y);
    returnPos.setObjPos(aList[index]);
}