#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __AROADover_h__
#define __AROADover_h__

 #include "IRawDataBuffer.h"
// #include "RawDataBuffer.h"
// #include "IChannelsMixing.h"
// #include "ROADdataBuffer.h"
// #include "ROADManager.h"
// #include "FractalDataContainerCollection.h"
#include "ROADoverDecodingOptions.h"
#include "DoubleContainer.h"
#include "Result.h"

#include "roadover_global.h"


typedef long long int64;

namespace ROADover
{
	class RawDataBuffer;
	class IChannelsMixing;
	class ROADdataBuffer;
	class ROADManager;
	class FractalDataContainerCollection;
	class ROADoverDecodingOptions;
	// enum Result;
	class AROADover;
    class IRawDataBuffer;
    class DoubleContainer;
}

namespace ROADover
{
    class ROADOVERSHARED_EXPORT AROADover
	{
		private: ROADover::RawDataBuffer* _dataBuffer;
		private: ROADover::IChannelsMixing* _channelsMixing;
		private: ROADover::ROADdataBuffer* _buffer;
		private: ROADover::ROADManager* _manager;
		private: ROADover::FractalDataContainerCollection* _fractalDataCollection;
        protected: ROADover::ROADoverDecodingOptions _options;
        private: ROADover::DoubleContainer _doubleContainer;

        public: virtual int64 readROADdata(char* aData) = 0;

		public: virtual unsigned int readAver(double* aData) = 0;

        public: virtual unsigned int convertByteArrayIntoDoubleArray(const char* aByteData, unsigned int aLengthByteArray, double* aDoubleData) = 0;

        public: virtual void writeRawData(ROADover::IRawDataBuffer* aRawDataBuffer) = 0;

		public: AROADover(ROADover::ROADoverDecodingOptions aOptions);

        public: virtual ~AROADover();

		public: int doOneDecoding();
	};
}

#endif
