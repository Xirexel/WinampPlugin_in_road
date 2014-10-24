#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __RawDataBuffer_h__
#define __RawDataBuffer_h__

//#include "IDoubleDataBuffer.h"
#include "DoubleContainer.h"
#include "IRawDataBuffer.h"

namespace ROADdecoding
{
	class IDoubleDataBuffer;
}
namespace ROADover
{
	class DoubleContainer;
	class IRawDataBuffer;
	class RawDataBuffer;
}

namespace ROADover
{
	class RawDataBuffer: public ROADover::IRawDataBuffer
	{
		private: unsigned int _length;
		private: unsigned int _count;
		public: std::vector<ROADover::DoubleContainer*> _doubleContainers;

		public: RawDataBuffer(unsigned int aLength, unsigned int aCount);

        public: virtual ~RawDataBuffer();

		public: ROADdecoding::IDoubleDataBuffer* getIDoubleDataBuffer(unsigned int aIndex);

		public: unsigned int getLength();

		public: unsigned int getCount();
	};
}

#endif
