#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __NoneMixingChannels_h__
#define __NoneMixingChannels_h__

#include "IChannelsMixing.h"


namespace ROADover
{
	class IChannelsMixing;
	class NoneMixingChannels;
    class IRawDataBuffer;
}

namespace ROADover
{
	class NoneMixingChannels: public ROADover::IChannelsMixing
	{

        public: void compute(ROADover::IRawDataBuffer* aBuffer);

        public: virtual ~NoneMixingChannels();
	};
}

#endif
