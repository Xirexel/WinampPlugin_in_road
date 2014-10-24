#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "FractalDataContainerCollection.h"
#include "../ROAD/IFractalDataContainer.h"
#include "FractalDataContainer.h"
#include "IFractalDataContainerCollection.h"

ROADdecoding::IFractalDataContainer* ROADover::FractalDataContainerCollection::getIFractalDataContainer(unsigned int aIndex) {
    return this->_collection.at(aIndex);
}

unsigned int ROADover::FractalDataContainerCollection::getCount() {
    return this->_count;
}

ROADover::FractalDataContainerCollection::FractalDataContainerCollection(unsigned int aIndex, unsigned int aLength)
    : _count(aIndex)
{
    for(unsigned int lindex = 0;
        lindex < aIndex;
        ++lindex)
    {
        _collection.push_back(new ROADover::FractalDataContainer(aLength));
    }

}

ROADover::FractalDataContainerCollection::~FractalDataContainerCollection()
{
    for(unsigned int lindex = 0;
        lindex < _count;
        ++lindex)
    {
        delete _collection.at(lindex);
    }
}
