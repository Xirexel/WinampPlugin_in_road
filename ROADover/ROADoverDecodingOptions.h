#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __ROADoverDecodingOptions_h__
#define __ROADoverDecodingOptions_h__

#include "MixingChannelsMode.h"
#include "ROADFormat.h"
#include "roadover_global.h"

namespace ROADover
{
	// enum MixingChannelsMode;
	// enum ROADFormat;
	class ROADoverDecodingOptions;
}

namespace ROADover
{
    class ROADOVERSHARED_EXPORT ROADoverDecodingOptions
	{
		private: ROADover::MixingChannelsMode _mixingChannelsMode;
		private: unsigned int _channels;
		private: unsigned int _superframeLength;
		private: unsigned int _frameRangLength;
		private: unsigned int _bitsPerSample;
		private: ROADover::ROADFormat _format;
		private: unsigned int _samplesPerRang;
		private: unsigned int _amountOfChannels;
		private: unsigned int _relativeDomainShift;
		private: unsigned int _scaleDomainShift;

		public: void setMixingChannelsMode(ROADover::MixingChannelsMode aMixingChannelsMode);

		public: ROADover::MixingChannelsMode getMixingChannelsMode();

		public: void setChannels(unsigned int aChannels);

		public: unsigned int getChannels();

		public: void setSuperframeLength(unsigned int aSuperframeLength);

		public: unsigned int getSuperframeLength();

		public: void setFrameRangLength(unsigned int aFrameRangLength);

		public: unsigned int getFrameRangLength();

		public: void setBitsPerSample(unsigned int aBitsPerSample);

		public: unsigned int getBitsPerSample();

		public: void setSamplesPerRang(unsigned int aSamplesPerRang);

		public: unsigned int getSamplesPerRang();

		public: void setAmountOfChannels(unsigned int aAmountOfChannels);

		public: unsigned int getAmountOfChannels();

		public: void setRelativeDomainShift(unsigned int aRelativeDomainShift);

		public: unsigned int getRelativeDomainShift();

		public: void setScaleDomainShift(unsigned int aScaleDomainShift);

		public: unsigned int getScaleDomainShift();
	};
}

#endif
