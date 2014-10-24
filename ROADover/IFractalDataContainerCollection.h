#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IFractalDataContainerCollection_h__
#define __IFractalDataContainerCollection_h__

// #include "IFractalDataContainer.h"

namespace ROADdecoding
{
	class IFractalDataContainer;
}
namespace ROADover
{
	class IFractalDataContainerCollection;
}

namespace ROADover
{
	class IFractalDataContainerCollection
	{

		public: virtual ROADdecoding::IFractalDataContainer* getIFractalDataContainer(unsigned int aIndex) = 0;

		public: virtual unsigned int getCount() = 0;

        public: virtual ~IFractalDataContainerCollection(){}
	};
}

#endif
