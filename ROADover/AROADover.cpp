#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "AROADover.h"
#include "IRawDataBuffer.h"
#include "RawDataBuffer.h"
#include "IChannelsMixing.h"
#include "ROADdataBuffer.h"
#include "ROADManager.h"
#include "FractalDataContainerCollection.h"
#include "ROADoverDecodingOptions.h"
#include "LplusRMixingChannels.h"
#include "LminusRMixingChannels.h"
#include "NoneMixingChannels.h"


//#include <QString>


ROADover::AROADover::AROADover(ROADover::ROADoverDecodingOptions aOptions)
    : _dataBuffer(new ROADover::RawDataBuffer(aOptions.getSuperframeLength() * aOptions.getFrameRangLength() * aOptions.getSamplesPerRang(), aOptions.getAmountOfChannels())),
      _buffer(new ROADover::ROADdataBuffer((aOptions.getBitsPerSample() >> 3) * aOptions.getSuperframeLength() *
                                           aOptions.getAmountOfChannels() * aOptions.getFrameRangLength() * aOptions.getSamplesPerRang())),
      _manager(new ROADover::ROADManager(aOptions)),
      _fractalDataCollection(new ROADover::FractalDataContainerCollection(aOptions.getAmountOfChannels(), aOptions.getFrameRangLength() * aOptions.getSuperframeLength())),
      _options(aOptions),
      _doubleContainer(ROADover::DoubleContainer(aOptions.getSuperframeLength() * aOptions.getFrameRangLength() * aOptions.getSamplesPerRang()))
{
    switch(aOptions.getMixingChannelsMode())
    {
    case LplusR:
    _channelsMixing = new LplusRMixingChannels();
    break;

    case LminusR:
    _channelsMixing = new LminusRMixingChannels();
    break;

    case NONE:
    default:
    _channelsMixing = new NoneMixingChannels();
    break;    
    }


}

ROADover::AROADover::~AROADover()
{
    delete _dataBuffer;
    delete _channelsMixing;
    delete _buffer;
    delete _manager;
    delete _fractalDataCollection;
}

int ROADover::AROADover::doOneDecoding()
{
    int result = 0;

    int64 lLength = readROADdata(_buffer->getData());

	if (lLength == -1)
		return -1;

//    qDebug(QString("lLength: %1").arg(lLength).toStdString().c_str());

    unsigned int superFrameLengthLength = _options.getSuperframeLength() * _options.getFrameRangLength() * _options.getSamplesPerRang();


    unsigned int lChannels = _options.getAmountOfChannels();

    const char* lptrData = _buffer->getData();


    for(unsigned int lChannel = 0;
        lChannel < lChannels;
        ++lChannel)
    {
        ROADdecoding::IFractalDataContainer *lptrIFractalDataContainer = _fractalDataCollection->getIFractalDataContainer(lChannel);


        unsigned int* lptrLengths = lptrIFractalDataContainer->getLengths()->getData();

        unsigned char* lptrIndeces = lptrIFractalDataContainer->getIndeces()->getData();


        int lLength = superFrameLengthLength;


        unsigned int countIndeces = 0;

        unsigned char luctemp = 0;

        while(lLength > 0)
        {

            luctemp = *lptrData;

            ++lptrData;

            lptrIndeces[countIndeces] = luctemp;

            unsigned int lrangeLength;

            if((luctemp & 128) == 128)
            {
                lrangeLength = (1 << (luctemp & 127)) * _options.getSamplesPerRang();
            }
            else
            {
                lrangeLength = (1 << (luctemp >> 5)) * _options.getSamplesPerRang();
            }

            lptrLengths[countIndeces] = lrangeLength;

            lLength -= lrangeLength;

            ++countIndeces;
        }

        lptrIFractalDataContainer->getLengths()->setCount(countIndeces);

        lptrIFractalDataContainer->getIndeces()->setCount(countIndeces);


//        qDebug(QString("countIndeces: %1").arg(countIndeces).toStdString().c_str());
    }



    for(unsigned int lChannel = 1;
        lChannel < lChannels;
        ++lChannel)
    {
        ROADdecoding::IFractalDataContainer *lptrIFractalDataContainer = _fractalDataCollection->getIFractalDataContainer(lChannel);

        double *lptrAver = lptrIFractalDataContainer->getAver()->getData();

        unsigned int countIndeces = lptrIFractalDataContainer->getIndeces()->getCount();

        lptrIFractalDataContainer->getAver()->setCount(countIndeces);

        unsigned int lLengthByteArray = countIndeces * (_options.getBitsPerSample() >> 3);

        convertByteArrayIntoDoubleArray(lptrData, lLengthByteArray, lptrAver);

        lptrData += lLengthByteArray;


//        qDebug(QString("countIndeces: %1").arg(countIndeces).toStdString().c_str());

    }



    for(unsigned int lChannel = 0;
        lChannel < lChannels;
        ++lChannel)
    {
        ROADdecoding::IFractalDataContainer *lptrIFractalDataContainer = _fractalDataCollection->getIFractalDataContainer(lChannel);


        unsigned char *lptrDomain = lptrIFractalDataContainer->getDomain()->getData();

        unsigned int countIndeces = lptrIFractalDataContainer->getIndeces()->getCount();

        unsigned char* lptrIndeces = lptrIFractalDataContainer->getIndeces()->getData();

        unsigned char ldomainIndex;

        unsigned char lindex;

        unsigned int countDomainIndeces = 0;

        while(countIndeces > 0)
        {
            lindex = *lptrIndeces;


            if((lindex & 128) == 0)
            {

                ldomainIndex = *lptrData;

                ++lptrData;

                *lptrDomain = ldomainIndex;

                ++lptrDomain;

                ++countDomainIndeces;
            }

            --countIndeces;

            ++lptrIndeces;
        }

        lptrIFractalDataContainer->getDomain()->setCount(countDomainIndeces);


//        qDebug(QString("countDomainIndeces: %1").arg(countDomainIndeces).toStdString().c_str());

    }



    for(unsigned int lChannel = 0;
        lChannel < lChannels;
        ++lChannel)
    {
        ROADdecoding::IFractalDataContainer *lptrIFractalDataContainer = _fractalDataCollection->getIFractalDataContainer(lChannel);



        unsigned char *lptrScales = lptrIFractalDataContainer->getScales()->getData();

        unsigned int countIndeces = lptrIFractalDataContainer->getIndeces()->getCount();

        unsigned char *lptrIndeces = lptrIFractalDataContainer->getIndeces()->getData();

        unsigned char lscale;

        unsigned char lindex;

        unsigned int countScales = 0;

        while(countIndeces > 0)
        {
            lindex = *lptrIndeces;

            if((lindex & 128) == 0)
            {
                lscale = *lptrData;

                ++lptrData;

                *lptrScales = lscale;

                ++lptrScales;

                ++countScales;
            }

            --countIndeces;

            ++lptrIndeces;
        }


        lptrIFractalDataContainer->getScales()->setCount(countScales);

    }




    ROADdecoding::IFractalDataContainer *lptrIFractalDataContainer = _fractalDataCollection->getIFractalDataContainer(0);

    unsigned int countIndeces = lptrIFractalDataContainer->getIndeces()->getCount();

    lptrIFractalDataContainer->getAver()->setCount(countIndeces);

    readAver(_doubleContainer.getData());





    double* lptrDoubleData = _doubleContainer.getData();

    unsigned int* lptrLengths = lptrIFractalDataContainer->getLengths()->getData();

    double* lptrAver = lptrIFractalDataContainer->getAver()->getData();

    countIndeces = lptrIFractalDataContainer->getIndeces()->getCount();

    lptrIFractalDataContainer->getAver()->setCount(countIndeces);

    unsigned int count = 0;

    unsigned int lrabgeLength = 0;

    while(count < countIndeces)
    {
        *lptrAver = *lptrDoubleData;

        ++lptrAver;

        lrabgeLength = *lptrLengths;

        lrabgeLength /= _options.getSamplesPerRang();

        lptrDoubleData += lrabgeLength;

        lptrLengths++;

        ++count;
    }

    this->_manager->doDecoding(_dataBuffer, _fractalDataCollection);

    _channelsMixing->compute(_dataBuffer);

    writeRawData(_dataBuffer);

    return result;
}
