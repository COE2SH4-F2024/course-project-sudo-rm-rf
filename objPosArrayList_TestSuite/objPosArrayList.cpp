#include "objPosArrayList.h"
#include <stdexcept>

objPosArrayList::objPosArrayList() {
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity]; 
}



objPosArrayList::~objPosArrayList() {
    delete[] aList;
}

int objPosArrayList::getSize() const {
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos) {
    if (listSize >= arrayCapacity) {
        throw std::overflow_error("List is full");
    }
    for (int i = listSize; i > 0; --i) {
        aList[i] = aList[i - 1];
    }
    aList[0] = thisPos;
    ++listSize;
}

void objPosArrayList::insertTail(objPos thisPos) {
    if (listSize >= arrayCapacity) {
        throw std::overflow_error("List is full");
    }
    aList[listSize] = thisPos;
    ++listSize;
}

void objPosArrayList::removeHead() {
    if (listSize == 0) {
        throw std::underflow_error("List is empty");
    }
    for (int i = 0; i < listSize - 1; ++i) {
        aList[i] = aList[i + 1];
    }
    --listSize;
}

void objPosArrayList::removeTail() {
    if (listSize == 0) {
        throw std::underflow_error("List is empty");
    }
    --listSize;
}

objPos objPosArrayList::getHeadElement() const {
    if (listSize == 0) {
        throw std::underflow_error("List is empty");
    }
    return aList[0];
}

objPos objPosArrayList::getTailElement() const {
    if (listSize == 0) {
        throw std::underflow_error("List is empty");
    }
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const {
    if (index < 0 || index >= listSize) {  // Correct bounds check
        // Return a default objPos if the index is out of range (for empty or non-existing elements)
        return objPos();  
    }
    return aList[index];
}

