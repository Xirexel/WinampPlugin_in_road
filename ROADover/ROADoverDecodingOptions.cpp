#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ROADoverDecodingOptions.h"
#include "MixingChannelsMode.h"
#include "ROADFormat.h"

void ROADover::ROADoverDecodingOptions::setMixingChannelsMode(ROADover::MixingChannelsMode aMixingChannelsMode) {
	this->_mixingChannelsMode = aMixingChannelsMode;
}

ROADover::MixingChannelsMode ROADover::ROADoverDecodingOptions::getMixingChannelsMode() {
	return this->_mixingChannelsMode;
}

void ROADover::ROADoverDecodingOptions::setChannels(unsigned int aChannels) {
	this->_channels = aChannels;
}

unsigned int ROADover::ROADoverDecodingOptions::getChannels() {
	return this->_channels;
}

void ROADover::ROADoverDecodingOptions::setSuperframeLength(unsigned int aSuperframeLength) {
	this->_superframeLength = aSuperframeLength;
}

unsigned int ROADover::ROADoverDecodingOptions::getSuperframeLength() {
	return this->_superframeLength;
}

void ROADover::ROADoverDecodingOptions::setFrameRangLength(unsigned int aFrameRangLength) {
	this->_frameRangLength = aFrameRangLength;
}

unsigned int ROADover::ROADoverDecodingOptions::getFrameRangLength() {
	return this->_frameRangLength;
}

void ROADover::ROADoverDecodingOptions::setBitsPerSample(unsigned int aBitsPerSample) {
	this->_bitsPerSample = aBitsPerSample;
}

unsigned int ROADover::ROADoverDecodingOptions::getBitsPerSample() {
	return this->_bitsPerSample;
}

void ROADover::ROADoverDecodingOptions::setSamplesPerRang(unsigned int aSamplesPerRang) {
	this->_samplesPerRang = aSamplesPerRang;
}

unsigned int ROADover::ROADoverDecodingOptions::getSamplesPerRang() {
	return this->_samplesPerRang;
}

void ROADover::ROADoverDecodingOptions::setAmountOfChannels(unsigned int aAmountOfChannels) {
	this->_amountOfChannels = aAmountOfChannels;
}

unsigned int ROADover::ROADoverDecodingOptions::getAmountOfChannels() {
	return this->_amountOfChannels;
}

void ROADover::ROADoverDecodingOptions::setRelativeDomainShift(unsigned int aRelativeDomainShift) {
	this->_relativeDomainShift = aRelativeDomainShift;
}

unsigned int ROADover::ROADoverDecodingOptions::getRelativeDomainShift() {
	return this->_relativeDomainShift;
}

void ROADover::ROADoverDecodingOptions::setScaleDomainShift(unsigned int aScaleDomainShift) {
	this->_scaleDomainShift = aScaleDomainShift;
}

unsigned int ROADover::ROADoverDecodingOptions::getScaleDomainShift() {
	return this->_scaleDomainShift;
}

