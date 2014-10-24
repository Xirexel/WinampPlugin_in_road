#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __ROADdecodingOptions_h__
#define __ROADdecodingOptions_h__


#include "road_global.h"

namespace ROADdecoding
{
	// enum MixingChannelMode;
    class ROADdecodingOptions;
}

namespace ROADdecoding
{
    class ROADSHARED_EXPORT ROADdecodingOptions
    {
		private: unsigned int _frameLength;
		private: unsigned int _samplesPerRang;
		private: unsigned int _superFrameLength;
		private: unsigned int _amountOfChannels;
		private: unsigned int _relativeDomainShift;
        private: unsigned int _scaleDomainShift;

		public: void setFrameLength(unsigned int aFrameLength);

		public: unsigned int getFrameLength();

		public: void setSamplesPerRang(unsigned int aSamplesPerRang);

		public: unsigned int getSamplesPerRang();

		public: void setSuperFrameLength(unsigned int aSuperFrameLength);

		public: unsigned int getSuperFrameLength();

		public: void setAmountOfChannels(unsigned int aAmountOfChannels);

		public: unsigned int getAmountOfChannels();

		public: void setRelativeDomainShift(unsigned int aRelativeDomainShift);

		public: unsigned int getRelativeDomainShift();

		public: void setScaleDomainShift(unsigned int aScaleDomainShift);

		public: unsigned int getScaleDomainShift();
	};
}

#endif
