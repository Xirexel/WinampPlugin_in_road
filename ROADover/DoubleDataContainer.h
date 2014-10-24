#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __DoubleDataContainer_h__
#define __DoubleDataContainer_h__

 #include "../ROAD/IDoubleDataContainer.h"

namespace ROADdecoding
{
	class IDoubleDataContainer;
}
namespace ROADover
{
	class DoubleDataContainer;
}

namespace ROADover
{
	class DoubleDataContainer: public ROADdecoding::IDoubleDataContainer
	{
		private: unsigned int _count;
		private: double* _data;

		public: double* getData();

		public: unsigned int getCount();

		public: DoubleDataContainer(unsigned int aLength);

        public: virtual ~DoubleDataContainer();

		public: void setCount(unsigned int aValue);
	};
}

#endif
