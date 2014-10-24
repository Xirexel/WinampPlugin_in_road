#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IFractalItemContainer_h__
#define __IFractalItemContainer_h__

// #include "IFractalItem.h"

namespace ROADdecoding
{
	class IFractalItem;
	class IFractalItemContainer;
}

namespace ROADdecoding
{
	class IFractalItemContainer
	{

        public: virtual ROADdecoding::IFractalItem* getIFractalItem(unsigned int aIndex) = 0;

		public: virtual unsigned int getCount() = 0;

        public: virtual ~IFractalItemContainer(){}
	};
}

#endif
