#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "SuperFrameFractaItemCollection.h"
#include "FractalItemContainer.h"
#include "IFractalDataContainer.h"
#include "IFractalItemContainer.h"
#include "IUCharDataContainer.h"
#include "IDoubleDataContainer.h"
#include "IUIntDataContainer.h"




ROADdecoding::SuperFrameFractaItemCollection::SuperFrameFractaItemCollection(unsigned int aSuperFrameLength, unsigned int aMaxFrameLength, unsigned int aFrameSampleLength)
    : _length(aFrameSampleLength)
{
    for(unsigned int index = 0;
        index < aSuperFrameLength;
        ++index)
        _fractalItemCollections.push_back(new FractalItemContainer(aMaxFrameLength));

}

ROADdecoding::SuperFrameFractaItemCollection::~SuperFrameFractaItemCollection()
{
    for(unsigned int index = 0;
        index < _fractalItemCollections.size();
        ++index)
        delete _fractalItemCollections.at(index);

    _fractalItemCollections.clear();
}

void ROADdecoding::SuperFrameFractaItemCollection::populate(ROADdecoding::IFractalDataContainer* aFractalDataContainer) {


    double* lptrAver = aFractalDataContainer->getAver()->getData();

    unsigned char * lptrDomains = aFractalDataContainer->getDomain()->getData();

    unsigned char * lptrIndeces = aFractalDataContainer->getIndeces()->getData();

    unsigned int *lptrLengths = aFractalDataContainer->getLengths()->getData();

    unsigned char * lptrScales = aFractalDataContainer->getScales()->getData();



    for(unsigned int index = 0;
        index < _fractalItemCollections.size();
        ++index)
    {
        ROADdecoding::FractalItemContainer* item = _fractalItemCollections.at(index);

        item->reset();

        unsigned int lrangPosition = 0;

//        ROADdecoding::LogPrintOut::getInstance().printOutln(ROADdecoding::LogPrintOut::INFO_LEVEL, L"FractaItems list: ");

        while(lrangPosition < _length)
        {            

            FractalItem *lFractalItem = item->getNextFractalItem();

            unsigned int rangeLength = *lptrLengths;

            unsigned char luchar = *lptrIndeces;

            lFractalItem->setLength(rangeLength);

            lFractalItem->setAver(*lptrAver);

            if((luchar & 128) == 128)
                lFractalItem->setSilence(true);
            else
            {
                lFractalItem->setSilence(false);

                lFractalItem->setForwardDirection((luchar & 16) == 16);

                unsigned int lDomainIndex = (luchar & 7) << 8;

                lDomainIndex |= *lptrDomains;

                lFractalItem->setDomainIndex(lDomainIndex);

                unsigned char ldecimScale = *lptrScales;

                double lScale = static_cast<double> (ldecimScale) / 255.0;

                if((luchar & 8) == 8)
                    lScale = -lScale;

                lFractalItem->setScale(lScale);


                ++lptrDomains;

                ++lptrScales;

            }

            lFractalItem->setPosition(lrangPosition);


//            ROADdecoding::LogPrintOut::getInstance().printOutln(ROADdecoding::LogPrintOut::INFO_LEVEL,
//                                                                   L"FractalItem aver: ", lFractalItem->getAver());

//            ROADdecoding::LogPrintOut::getInstance().printOutln(ROADdecoding::LogPrintOut::INFO_LEVEL,
//                                                                   L"FractalItem length: ", lFractalItem->getLength());

//            ROADdecoding::LogPrintOut::getInstance().printOutln(ROADdecoding::LogPrintOut::INFO_LEVEL,
//                                                                   L"FractalItem isSilence: ", lFractalItem->isSilence());

//            ROADdecoding::LogPrintOut::getInstance().printOutln(ROADdecoding::LogPrintOut::INFO_LEVEL,
//                                                                   L"FractalItem domainIndex: ", lFractalItem->getDomainIndex());

//            ROADdecoding::LogPrintOut::getInstance().printOutln(ROADdecoding::LogPrintOut::INFO_LEVEL,
//                                                                   L"FractalItem scale: ", lFractalItem->getScale());

//            ROADdecoding::LogPrintOut::getInstance().printOutln(ROADdecoding::LogPrintOut::INFO_LEVEL,
//                                                                   L"FractalItem isForwardDirection: ", lFractalItem->isForwardDirection());







            lrangPosition += rangeLength;

            ++lptrLengths;

            ++lptrIndeces;

            ++lptrAver;
        }

    }

}

ROADdecoding::IFractalItemContainer* ROADdecoding::SuperFrameFractaItemCollection::getIFractalItemContainer(unsigned int aIndex) {
    return this->_fractalItemCollections.at(aIndex);
}

