#include <string>
#include <vector>
#include <list>
#include <exception>
using namespace std;

#ifndef __FractalDecoder_h__
#define __FractalDecoder_h__

#include "ROADdecodingOptions.h"
#include "SuperFrameFractaItemCollection.h"
#include "DomainProcessor.h"
// #include "IFractalDataContainer.h"
// #include "IFractalItemContainer.h"

#include "road_global.h"


namespace ROADdecoding
{
    class ROADdecodingOptions;
	class SuperFrameFractaItemCollection;
	class DomainProcessor;
	class IFractalDataContainer;
	class IFractalItemContainer;
    class ROADdecoder;
    class IDoubleDataBuffer;
}

namespace ROADdecoding
{
    class ROADSHARED_EXPORT ROADdecoder
	{
        public: ROADdecoding::ROADdecodingOptions _options;
        public: ROADdecoding::SuperFrameFractaItemCollection _superFrameFractalItemCollection;
        public: ROADdecoding::DomainProcessor _domainProcessor;
        private: std::list<unsigned int> _listRN;

        public: ROADdecoder(ROADdecoding::ROADdecodingOptions aOptions);

        public: virtual ~ROADdecoder();

        public: void decode(ROADdecoding::IDoubleDataBuffer* aDataBuffer, ROADdecoding::IFractalDataContainer* aFractalDataContainer);

        private: void decodeFrame(double* aData, ROADdecoding::IFractalItemContainer* aFractalItemContainer);

		private: int getRNumber();

		private: void setRangeOfRNG(unsigned int aLowBoder, unsigned int aTopBorder);


	};
}

#endif
