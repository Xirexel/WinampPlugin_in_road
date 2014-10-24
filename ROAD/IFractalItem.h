#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __IFractalItem_h__
#define __IFractalItem_h__

namespace ROADdecoding
{
	class IFractalItem;
}

namespace ROADdecoding
{
	class IFractalItem
	{

		public: virtual double getAver() = 0;

		public: virtual unsigned int getLength() = 0;

		public: virtual bool isSilence() = 0;

		public: virtual bool isForwardDirection() = 0;

		public: virtual unsigned int getDomainIndex() = 0;

		public: virtual double getScale() = 0;

		public: virtual unsigned int getPosition() = 0;

        public: virtual ~IFractalItem(){}
	};
}

#endif
