#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FractalItem_h__
#define __FractalItem_h__

 #include "IFractalItem.h"

namespace ROADdecoding
{
	class IFractalItem;
	class FractalItem;
}

namespace ROADdecoding
{
    class FractalItem: public ROADdecoding::IFractalItem
	{
		private: double _aver;
		private: unsigned int _length;
		private: bool _silence;
		private: bool _forwardDirection;
		private: unsigned int _domainIndex;
		private: double _scale;
		private: unsigned int _position;

		public: double getAver();

		public: unsigned int getLength();

		public: bool isSilence();

		public: bool isForwardDirection();

		public: unsigned int getDomainIndex();

		public: double getScale();

		public: unsigned int getPosition();

		public: void setAver(double aAver);

		public: void setLength(unsigned int aLength);

		public: void setSilence(bool aSilence);

		public: void setForwardDirection(bool aForwardDirection);

		public: void setDomainIndex(unsigned int aDomainIndex);

		public: void setScale(double aScale);

		public: void setPosition(unsigned int aPosition);

        public: virtual ~FractalItem();
	};
}

#endif
