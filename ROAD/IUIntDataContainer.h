#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IUIntDataContainer_h__
#define __IUIntDataContainer_h__

namespace ROADdecoding
{
	class IUIntDataContainer;
}

namespace ROADdecoding
{
	class IUIntDataContainer
	{

		public: virtual unsigned int* getData() = 0;

		public: virtual unsigned int getCount() = 0;

		public: virtual void setCount(unsigned int aValue) = 0;

        public: virtual ~IUIntDataContainer(){}
	};
}

#endif
