#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IDoubleDataContainer_h__
#define __IDoubleDataContainer_h__

namespace ROADdecoding
{
	class IDoubleDataContainer;
}

namespace ROADdecoding
{
	class IDoubleDataContainer
	{

		public: virtual double* getData() = 0;

		public: virtual unsigned int getCount() = 0;

		public: virtual void setCount(unsigned int aValue) = 0;

        public: virtual ~IDoubleDataContainer(){}
	};
}

#endif
