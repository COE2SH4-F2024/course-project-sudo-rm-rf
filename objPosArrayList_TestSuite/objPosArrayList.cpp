#include "objPosArrayList.h"
#include <stdexcept>

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[200];
    listSize = 0;
    arrayCapacity = 200;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        for (int i = listSize; i > 0; --i)
    {
        aList[i] = aList[i - 1];
    }
    aList[0] = thisPos;
    ++listSize;
    }
    
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        aList[listSize] = thisPos;
        ++listSize;
    }
}

void objPosArrayList::removeHead()
{
    for (int i = 0; i < listSize - 1; ++i)
    {
        aList[i] = aList[i + 1];
    }
    --listSize;
}

void objPosArrayList::removeTail()
{
    aList[listSize - 1] = objPos();
    --listSize;
}

objPos objPosArrayList::getHeadElement() const
{

    return aList[0];

}

objPos objPosArrayList::getTailElement() const
{

    return aList[listSize - 1];
    
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}