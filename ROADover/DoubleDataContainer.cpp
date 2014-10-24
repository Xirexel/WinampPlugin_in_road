#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "DoubleDataContainer.h"
#include "../ROAD/IDoubleDataContainer.h"

double* ROADover::DoubleDataContainer::getData() {
    return this->_data;
}

unsigned int ROADover::DoubleDataContainer::getCount() {
    return this->_count;
}

ROADover::DoubleDataContainer::DoubleDataContainer(unsigned int aLength)
    : _data(new double[aLength])
{
}

void ROADover::DoubleDataContainer::setCount(unsigned int aValue) {
    this->_count = aValue;
}

ROADover::DoubleDataContainer::~DoubleDataContainer()
{
    delete []_data;
}
