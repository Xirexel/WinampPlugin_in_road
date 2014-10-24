#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IDoubleDataBuffer_h__
#define __IDoubleDataBuffer_h__

namespace ROADdecoding
{
	class IDoubleDataBuffer;
}

namespace ROADdecoding
{
	class IDoubleDataBuffer
	{

		public: virtual double* getData() = 0;

		public: virtual unsigned int getLength() = 0;

        public: virtual ~IDoubleDataBuffer(){}
	};
}

#endif
