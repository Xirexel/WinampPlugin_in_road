#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IChannelsMixing_h__
#define __IChannelsMixing_h__

#include "IRawDataBuffer.h"


namespace ROADover
{
	class IChannelsMixing;
    class IRawDataBuffer;
}

namespace ROADover
{
	class IChannelsMixing
	{

        public: virtual void compute(ROADover::IRawDataBuffer* aBuffer) = 0;

        public: virtual ~IChannelsMixing(){}
	};
}

#endif
