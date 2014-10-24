#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "UCharDataContainer.h"
#include "../ROAD/IUCharDataContainer.h"

unsigned char* ROADover::UCharDataContainer::getData() {
    return this->_data;
}

unsigned int ROADover::UCharDataContainer::getCount() {
    return this->_count;
}

ROADover::UCharDataContainer::UCharDataContainer(unsigned int aLength)
    : _data(new unsigned char[aLength])
{
}

void ROADover::UCharDataContainer::setCount(unsigned int aValue) {
    this->_count = aValue;
}

ROADover::UCharDataContainer::~UCharDataContainer()
{
    delete [](this->_data);
}
