#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FractalItemContainer_h__
#define __FractalItemContainer_h__

#include "FractalItem.h"
// #include "IFractalItem.h"
 #include "IFractalItemContainer.h"

namespace ROADdecoding
{
	class FractalItem;
	class IFractalItem;
	class IFractalItemContainer;
	class FractalItemContainer;
}

namespace ROADdecoding
{
    class FractalItemContainer: public ROADdecoding::IFractalItemContainer
	{
		private: unsigned int _count;
        public: std::vector<ROADdecoding::FractalItem*> _fractalItemCollecrion;

        public: ROADdecoding::IFractalItem* getIFractalItem(unsigned int aIndex);

		public: unsigned int getCount();

		public: void reset();

        public: ROADdecoding::FractalItem* getNextFractalItem();

        public: FractalItemContainer(unsigned int aLength);

        public: virtual ~FractalItemContainer();
	};
}

#endif
