#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ROADManager.h"
#include "../ROAD/ROADdecoder.h"
#include "IRawDataBuffer.h"
#include "ROADoverDecodingOptions.h"
#include "IFractalDataContainerCollection.h"

ROADover::ROADManager::ROADManager(ROADover::ROADoverDecodingOptions aOptions)
{
    ROADdecoding::ROADdecodingOptions lOptions;

    lOptions.setAmountOfChannels(aOptions.getAmountOfChannels());

    lOptions.setFrameLength(aOptions.getFrameRangLength());

    lOptions.setRelativeDomainShift(aOptions.getRelativeDomainShift());

    lOptions.setSamplesPerRang(aOptions.getSamplesPerRang());

    lOptions.setScaleDomainShift(aOptions.getScaleDomainShift());

    lOptions.setSuperFrameLength(aOptions.getSuperframeLength());




    for(unsigned int lIndex = 0;
        lIndex < aOptions.getAmountOfChannels();
        ++lIndex)
    {
        _channelDecoders.push_back(new ROADdecoding::ROADdecoder(lOptions));
    }
}

void ROADover::ROADManager::doDecoding(ROADover::IRawDataBuffer* aDataBuffer, ROADover::IFractalDataContainerCollection* aFractalItemArray) {

    for(unsigned int lIndex = 0;
        lIndex < _channelDecoders.size();
        ++lIndex)
    {
        _channelDecoders.at(lIndex)->decode(aDataBuffer->getIDoubleDataBuffer(lIndex), aFractalItemArray->getIFractalDataContainer(lIndex));
    }
}

ROADover::ROADManager::~ROADManager()
{
    std::vector<ROADdecoding::ROADdecoder*>::iterator lBegin = this->_channelDecoders.begin();

    std::vector<ROADdecoding::ROADdecoder*>::iterator lEnd = this->_channelDecoders.end();

    while(lBegin != lEnd)
    {
        delete (*lBegin);

        ++lBegin;
    }

}
