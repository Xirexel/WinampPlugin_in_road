#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __ROADManager_h__
#define __ROADManager_h__

#include "../ROAD/ROADdecoder.h"
#include "IRawDataBuffer.h"
#include "ROADoverDecodingOptions.h"
// #include "IFractalDataContainerCollection.h"

namespace ROADdecoding
{
    class ROADdecoder;
}
namespace ROADover
{
	class ROADoverDecodingOptions;
	class IFractalDataContainerCollection;
	class ROADManager;
    class IRawDataBuffer;
}

namespace ROADover
{
	class ROADManager
	{
		public: std::vector<ROADdecoding::ROADdecoder*> _channelDecoders;

		public: ROADManager(ROADover::ROADoverDecodingOptions aOptions);

        public: virtual ~ROADManager();

        public: void doDecoding(ROADover::IRawDataBuffer* aDataBuffer, ROADover::IFractalDataContainerCollection* aFractalItemArray);
	};
}

#endif
