#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "RawDataBuffer.h"
#include "../ROAD/IDoubleDataBuffer.h"
#include "DoubleContainer.h"
#include "IRawDataBuffer.h"

ROADover::RawDataBuffer::RawDataBuffer(unsigned int aLength, unsigned int aCount)
    : _count(aCount),
      _length(aLength)
{
    for(unsigned int lIndex = 0;
        lIndex < aCount;
        ++lIndex)
    {
        this->_doubleContainers.push_back(new ROADover::DoubleContainer(aLength));
    }
}

ROADdecoding::IDoubleDataBuffer* ROADover::RawDataBuffer::getIDoubleDataBuffer(unsigned int aIndex) {
    return this->_doubleContainers.at(aIndex);
}

unsigned int ROADover::RawDataBuffer::getLength() {
    return this->_length;
}

unsigned int ROADover::RawDataBuffer::getCount() {
    return this->_count;
}

ROADover::RawDataBuffer::~RawDataBuffer()
{
    for(unsigned int lIndex = 0;
        lIndex < this->_count;
        ++lIndex)
    {
        delete this->_doubleContainers.at(lIndex);
    }
}
