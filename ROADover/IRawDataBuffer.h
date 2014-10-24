#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IRawDataBuffer_h__
#define __IRawDataBuffer_h__

#include "../ROAD/IDoubleDataBuffer.h"

namespace ROADdecoding
{
	class IDoubleDataBuffer;
}
namespace ROADover
{
	class IRawDataBuffer;
}

namespace ROADover
{
	class IRawDataBuffer
	{

		public: virtual ROADdecoding::IDoubleDataBuffer* getIDoubleDataBuffer(unsigned int aIndex) = 0;

		public: virtual unsigned int getLength() = 0;

		public: virtual unsigned int getCount() = 0;
	};
}

#endif
