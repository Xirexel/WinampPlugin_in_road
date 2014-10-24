#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "DoubleContainer.h"
#include "../ROAD/IDoubleDataBuffer.h"

ROADover::DoubleContainer::DoubleContainer(unsigned int aLength)
    : _data(new double[aLength]),
      _length(aLength)
{
}

double* ROADover::DoubleContainer::getData() {
    return this->_data;
}

unsigned int ROADover::DoubleContainer::getLength() {
    return this->_length;
}

ROADover::DoubleContainer::~DoubleContainer()
{
    delete []this->_data;
}
