#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ROADdecodingOptions.h"

void ROADdecoding::ROADdecodingOptions::setFrameLength(unsigned int aFrameLength) {
	this->_frameLength = aFrameLength;
}

unsigned int ROADdecoding::ROADdecodingOptions::getFrameLength() {
	return this->_frameLength;
}

void ROADdecoding::ROADdecodingOptions::setSamplesPerRang(unsigned int aSamplesPerRang) {
	this->_samplesPerRang = aSamplesPerRang;
}

unsigned int ROADdecoding::ROADdecodingOptions::getSamplesPerRang() {
	return this->_samplesPerRang;
}

void ROADdecoding::ROADdecodingOptions::setSuperFrameLength(unsigned int aSuperFrameLength) {
	this->_superFrameLength = aSuperFrameLength;
}

unsigned int ROADdecoding::ROADdecodingOptions::getSuperFrameLength() {
	return this->_superFrameLength;
}

void ROADdecoding::ROADdecodingOptions::setAmountOfChannels(unsigned int aAmountOfChannels) {
	this->_amountOfChannels = aAmountOfChannels;
}

unsigned int ROADdecoding::ROADdecodingOptions::getAmountOfChannels() {
	return this->_amountOfChannels;
}

void ROADdecoding::ROADdecodingOptions::setRelativeDomainShift(unsigned int aRelativeDomainShift) {
	this->_relativeDomainShift = aRelativeDomainShift;
}

unsigned int ROADdecoding::ROADdecodingOptions::getRelativeDomainShift() {
	return this->_relativeDomainShift;
}

void ROADdecoding::ROADdecodingOptions::setScaleDomainShift(unsigned int aScaleDomainShift) {
	this->_scaleDomainShift = aScaleDomainShift;
}

unsigned int ROADdecoding::ROADdecodingOptions::getScaleDomainShift() {
	return this->_scaleDomainShift;
}

