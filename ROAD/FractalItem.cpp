#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "FractalItem.h"
#include "IFractalItem.h"

double ROADdecoding::FractalItem::getAver() {
    return this->_aver;
}

unsigned int ROADdecoding::FractalItem::getLength() {
    return this->_length;
}

bool ROADdecoding::FractalItem::isSilence() {
    return this->_silence;
}

bool ROADdecoding::FractalItem::isForwardDirection() {
    return this->_forwardDirection;
}

unsigned int ROADdecoding::FractalItem::getDomainIndex() {
    return this->_domainIndex;
}

double ROADdecoding::FractalItem::getScale() {
    return this->_scale;
}

void ROADdecoding::FractalItem::setAver(double aAver) {
	this->_aver = aAver;
}

void ROADdecoding::FractalItem::setLength(unsigned int aLength) {
	this->_length = aLength;
}

void ROADdecoding::FractalItem::setSilence(bool aSilence) {
	this->_silence = aSilence;
}

void ROADdecoding::FractalItem::setForwardDirection(bool aForwardDirection) {
	this->_forwardDirection = aForwardDirection;
}

void ROADdecoding::FractalItem::setDomainIndex(unsigned int aDomainIndex) {
	this->_domainIndex = aDomainIndex;
}

void ROADdecoding::FractalItem::setScale(double aScale) {
	this->_scale = aScale;
}

unsigned int ROADdecoding::FractalItem::getPosition()
{
    return this->_position;
}

void ROADdecoding::FractalItem::setPosition(unsigned int aPosition)
{
    this->_position = aPosition;
}

ROADdecoding::FractalItem::~FractalItem()
{

}
