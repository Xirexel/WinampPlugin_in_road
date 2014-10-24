#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __LminusRMixingChannels_h__
#define __LminusRMixingChannels_h__

// #include "IRawDataBuffer.h"
#include "IChannelsMixing.h"

namespace ROADdecoding
{
	class IRawDataBuffer;
}
namespace ROADover
{
	class IChannelsMixing;
	class LminusRMixingChannels;
}

namespace ROADover
{
	class LminusRMixingChannels: public ROADover::IChannelsMixing
	{

        public: void compute(ROADover::IRawDataBuffer* aBuffer);

        public: virtual ~LminusRMixingChannels();
	};
}

#endif
