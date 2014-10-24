#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __LplusRMixingChannels_h__
#define __LplusRMixingChannels_h__

// #include "IRawDataBuffer.h"
#include "IChannelsMixing.h"


namespace ROADover
{
	class IChannelsMixing;
	class LplusRMixingChannels;
    class IRawDataBuffer;
}

namespace ROADover
{
	class LplusRMixingChannels: public ROADover::IChannelsMixing
	{

        public: void compute(ROADover::IRawDataBuffer* aBuffer);

        public: virtual ~LplusRMixingChannels();
	};
}

#endif
