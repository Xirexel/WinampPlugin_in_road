#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __DoubleContainer_h__
#define __DoubleContainer_h__

#include "../ROAD/IDoubleDataBuffer.h"

namespace ROADdecoding
{
	class IDoubleDataBuffer;
}
namespace ROADover
{
	class DoubleContainer;
}

namespace ROADover
{
	class DoubleContainer: public ROADdecoding::IDoubleDataBuffer
	{
		private: double* _data;
		private: unsigned int _length;

		public: DoubleContainer(unsigned int aLength);

        public: virtual ~DoubleContainer();

		public: double* getData();

		public: unsigned int getLength();
	};
}

#endif
