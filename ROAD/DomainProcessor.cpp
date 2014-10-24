#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "DomainProcessor.h"
ROADdecoding::DomainProcessor::DomainProcessor(unsigned int aMaxLength)
    : _data(new double [aMaxLength])
{
}

ROADdecoding::DomainProcessor::~DomainProcessor()
{
    delete []_data;
}

double* ROADdecoding::DomainProcessor::process(double* aData, unsigned int aLength, unsigned int aSamplePerRange, unsigned int aDomainIndex, unsigned int aRelativeDomainSfift, unsigned int aScaleDomainShift, bool aForwardDirection) {

    double lscaleDomainOffset = (static_cast<double>(aSamplePerRange)/static_cast<double>(aScaleDomainShift));

    unsigned int ldpmainOffset = static_cast<unsigned int>(static_cast<double>(aDomainIndex) * (lscaleDomainOffset));

    double lAver = 0.0;

    double lTmepValue = 0;

    unsigned int lOffset = 0;

    for(unsigned int index = 0;
        index < aLength;
        ++index)
    {
        lOffset = ldpmainOffset + (index << 1);

        lTmepValue = (aData[lOffset] + aData[lOffset + 1]) * 0.5;

        lAver += lTmepValue;

        _data[index] = lTmepValue;
    }

    lAver /= aLength;

    for(unsigned int index = 0;
        index < aLength;
        ++index)
    {
        _data[index] = _data[index] - lAver;
    }

    if(aForwardDirection)
    {
        backShrink(_data, aLength, aRelativeDomainSfift, aScaleDomainShift);
    }

    return _data;
}

void ROADdecoding::DomainProcessor::backShrink(double* aData, unsigned int aLength, unsigned int aRelativeDomainSfift, unsigned int aScaleDomainShift) {

    double lTempValue;

    unsigned int lHalfLength = aLength >> 1;

    for(unsigned int index = 0;
        index < lHalfLength;
        ++index)
    {
        lTempValue = aData[index];

        aData[index] = aData[aLength - 1 - index];

        aData[aLength - 1 - index] = lTempValue;
    }
}

