#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ROADdataBuffer.h"
ROADover::ROADdataBuffer::ROADdataBuffer(unsigned int aLength)
    : _data(new char[aLength])
{
}

char* ROADover::ROADdataBuffer::getData() {
	return this->_data;
}

ROADover::ROADdataBuffer::~ROADdataBuffer()
{
    delete []_data;
}
