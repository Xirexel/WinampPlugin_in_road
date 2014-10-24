#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IFractalDataContainer_h__
#define __IFractalDataContainer_h__

// #include "IDoubleDataContainer.h"
// #include "IUCharDataContainer.h"
// #include "IUIntDataContainer.h"

namespace ROADdecoding
{
	class IDoubleDataContainer;
	class IUCharDataContainer;
	class IUIntDataContainer;
	class IFractalDataContainer;
}

namespace ROADdecoding
{
	class IFractalDataContainer
	{

        public: virtual ROADdecoding::IDoubleDataContainer* getAver() = 0;

        public: virtual ROADdecoding::IUCharDataContainer* getIndeces() = 0;

        public: virtual ROADdecoding::IUCharDataContainer* getDomain() = 0;

        public: virtual ROADdecoding::IUCharDataContainer* getScales() = 0;

        public: virtual ROADdecoding::IUIntDataContainer* getLengths() = 0;

        public: virtual ~IFractalDataContainer(){}
	};
}

#endif
