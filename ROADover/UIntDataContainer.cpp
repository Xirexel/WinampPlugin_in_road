#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "UIntDataContainer.h"
#include "../ROAD/IUIntDataContainer.h"

unsigned int* ROADover::UIntDataContainer::getData() {
    return this->_data;
}

unsigned int ROADover::UIntDataContainer::getCount() {
    return this->_count;
}

void ROADover::UIntDataContainer::setCount(unsigned int aValue) {
    this->_count = aValue;
}

ROADover::UIntDataContainer::UIntDataContainer(unsigned int aLength)
    : _count(0),
      _data(new unsigned int[aLength])
{
}

ROADover::UIntDataContainer::~UIntDataContainer()
{
    delete [](this->_data);
}
