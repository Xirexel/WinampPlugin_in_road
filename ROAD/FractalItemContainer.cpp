#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "FractalItemContainer.h"
#include "FractalItem.h"
#include "IFractalItem.h"
#include "IFractalItemContainer.h"

ROADdecoding::IFractalItem* ROADdecoding::FractalItemContainer::getIFractalItem(unsigned int aIndex) {
    return _fractalItemCollecrion.at(aIndex);
}

unsigned int ROADdecoding::FractalItemContainer::getCount() {
    return this->_count;
}

void ROADdecoding::FractalItemContainer::reset() {
    this->_count = 0;
}

ROADdecoding::FractalItem* ROADdecoding::FractalItemContainer::getNextFractalItem() {

    unsigned int t = this->_count;

    this->_count++;

    return _fractalItemCollecrion.at(t);
}

ROADdecoding::FractalItemContainer::FractalItemContainer(unsigned int aLength) {

    for(unsigned int index = 0;
        index < aLength;
        ++index)
    {
        _fractalItemCollecrion.push_back(new FractalItem);
    }
}

ROADdecoding::FractalItemContainer::~FractalItemContainer()
{
    for(unsigned int index = 0;
        index < _fractalItemCollecrion.size();
        ++index)
    {
        delete _fractalItemCollecrion.at(index);
    }

    _fractalItemCollecrion.clear();
}
