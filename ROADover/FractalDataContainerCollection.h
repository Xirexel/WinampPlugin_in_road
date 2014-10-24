#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FractalDataContainerCollection_h__
#define __FractalDataContainerCollection_h__

// #include "IFractalDataContainer.h"
#include "FractalDataContainer.h"
#include "IFractalDataContainerCollection.h"

namespace ROADdecoding
{
	class IFractalDataContainer;
}
namespace ROADover
{
	class FractalDataContainer;
	class IFractalDataContainerCollection;
	class FractalDataContainerCollection;
}

namespace ROADover
{
	class FractalDataContainerCollection: public ROADover::IFractalDataContainerCollection
	{
        private: unsigned int _count;
        private: std::vector<ROADover::FractalDataContainer*> _collection;

		public: ROADdecoding::IFractalDataContainer* getIFractalDataContainer(unsigned int aIndex);

		public: unsigned int getCount();

        public: FractalDataContainerCollection(unsigned int aIndex, unsigned int aLength);

        public: virtual ~FractalDataContainerCollection();
	};
}

#endif
