#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "LplusRMixingChannels.h"
#include "IRawDataBuffer.h"
#include "IChannelsMixing.h"

void ROADover::LplusRMixingChannels::compute(ROADover::IRawDataBuffer* aBuffer) {

    int aLength = aBuffer->getLength();

    double * aFirstChannel = aBuffer->getIDoubleDataBuffer(0)->getData();

    double * aSecondChannel = aBuffer->getIDoubleDataBuffer(1)->getData();



    while(aLength > 0)
    {
        double sampleOfLeftChannel = (*aFirstChannel) + (*aSecondChannel);

        double sampleOfRightChannel = (*aFirstChannel) - (*aSecondChannel);

        *aFirstChannel = sampleOfLeftChannel;

        *aSecondChannel = sampleOfRightChannel;


        ++aFirstChannel;

        ++aSecondChannel;

        --aLength;
    }


}

ROADover::LplusRMixingChannels::~LplusRMixingChannels()
{

}
