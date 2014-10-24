#include <string>
#include <vector>
#include <exception>
//#include <random>
using namespace std;

#include "ROADdecoder.h"
#include "ROADdecodingOptions.h"
#include "SuperFrameFractaItemCollection.h"
#include "DomainProcessor.h"
#include "IFractalDataContainer.h"
#include "IFractalItemContainer.h"
#include "IFractalItem.h"
#include "IDoubleDataBuffer.h"


ROADdecoding::ROADdecoder::ROADdecoder(ROADdecoding::ROADdecodingOptions aOptions)
    : _options(aOptions),
      _superFrameFractalItemCollection(ROADdecoding::SuperFrameFractaItemCollection(aOptions.getSuperFrameLength(), aOptions.getFrameLength(),
                                                                                       aOptions.getFrameLength() * aOptions.getSamplesPerRang())),
      _domainProcessor(ROADdecoding::DomainProcessor(aOptions.getFrameLength() * aOptions.getSamplesPerRang()))
{
}

ROADdecoding::ROADdecoder::~ROADdecoder()
{

}

void ROADdecoding::ROADdecoder::decode(ROADdecoding::IDoubleDataBuffer* aDataBuffer, ROADdecoding::IFractalDataContainer* aFractalDataContainer) {

    this->_superFrameFractalItemCollection.populate(aFractalDataContainer);

    unsigned int frameCount = 0;

    unsigned int sampleFrameOffset = _options.getFrameLength() * _options.getSamplesPerRang();

    while(frameCount < _options.getSuperFrameLength())
    {
        IFractalItemContainer * lptrIFractalItemContainer = this->_superFrameFractalItemCollection.getIFractalItemContainer(frameCount);

        decodeFrame(aDataBuffer->getData() + frameCount * sampleFrameOffset, lptrIFractalItemContainer);

        ++frameCount;
    }

}

void ROADdecoding::ROADdecoder::decodeFrame(double* aData, ROADdecoding::IFractalItemContainer* aFractalItemContainer) {


    unsigned int countFractalItems = 0;

    double* lFramePos = aData;

    while(countFractalItems < aFractalItemContainer->getCount())
    {
        IFractalItem * item = aFractalItemContainer->getIFractalItem(countFractalItems);

        unsigned int lrangeLength = item->getLength();

        double lAver = item->getAver();

        for(unsigned int index = 0;
                index < lrangeLength;
                ++index)
        {
            *lFramePos = lAver;

            lFramePos++;
        }

        ++countFractalItems;
    }

//#ifdef NON_DETERINETED_DECODING

//    // Non-determinated algorithm of decoding

//    for(unsigned int index = 0;
//        index < 4;
//        ++index)
//    {
//        lFramePos = aData;

//        setRangeOfRNG(0, aFractalItemContainer->getCount());

//        int indexRange = getRNumber();

//        while(indexRange >= 0)
//        {
//            IFractalItem * item = aFractalItemContainer->getIFractalItem((unsigned int)indexRange);

//            unsigned int lrangeLength = item->getLength();

//            double lAver = item->getAver();

//            unsigned int lPosition = item->getPosition();

//            if(!item->isSilence())
//            {

//                bool lBackDirection = item->isForwardDirection();

//                unsigned int lDomainIndex = item->getDomainIndex();

//                double lScale = item->getScale();


//                double * lptrDomain = _domainProcessor.process(aData, lrangeLength, _options.getSamplesPerRang(), lDomainIndex, _options.getRelativeDomainShift(), _options.getScaleDomainShift(), lBackDirection);


//                for(decltype(lrangeLength) index = 0;
//                    index < lrangeLength;
//                    ++index)
//                {
//                    double t = lptrDomain[index] * lScale + lAver;

//                    lFramePos[lPosition + index] = t;
//                }
//            }

//            indexRange = getRNumber();
//        }
//    }

//#else

    // Determinated algorithm of decoding

    for(unsigned int index = 0;
        index < 6;
        ++index)
    {

        countFractalItems = 0;

        lFramePos = aData;

        while(countFractalItems < aFractalItemContainer->getCount())
        {
            IFractalItem * item = aFractalItemContainer->getIFractalItem(countFractalItems);

            unsigned int lrangeLength = item->getLength();

            double lAver = item->getAver();

            if(!item->isSilence())
            {

                bool lBackDirection = item->isForwardDirection();

                unsigned int lDomainIndex = item->getDomainIndex();

                double lScale = item->getScale();


                double * lptrDomain = _domainProcessor.process(aData, lrangeLength, _options.getSamplesPerRang(), lDomainIndex, _options.getRelativeDomainShift(), _options.getScaleDomainShift(), lBackDirection);


                for(unsigned int index = 0;
                    index < lrangeLength;
                    ++index)
                {
                    double t = lptrDomain[index] * lScale + lAver;

                    *lFramePos = t;

                    lFramePos++;
                }
            }
            else
            {
                lFramePos+=lrangeLength;
            }

            ++countFractalItems;
        }
    }

//#endif



}

int ROADdecoding::ROADdecoder::getRNumber()
{
    if(_listRN.empty())
        return -1;

    int result = _listRN.back();

    _listRN.pop_back();

    return result;


}

void ROADdecoding::ROADdecoder::setRangeOfRNG(unsigned int aLowBoder, unsigned int aTopBorder)
{
//    random_device f;

//    typedef random_device::result_type result_type;

//    result_type max = f.max();

//    while(aLowBoder < aTopBorder)
//    {
//        result_type value = f();

//        float normValue = (float)value / max;

//        if(normValue < 0.5)
//            this->_listRN.push_back(aLowBoder);
//        else
//            this->_listRN.push_front(aLowBoder);

//        ++aLowBoder;
//    }


}
