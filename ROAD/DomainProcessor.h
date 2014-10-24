#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __DomainProcessor_h__
#define __DomainProcessor_h__

namespace ROADdecoding
{
	class DomainProcessor;
}

namespace ROADdecoding
{
	class DomainProcessor
	{
		private: double* _data;

		public: DomainProcessor(unsigned int aMaxLength);

        public: virtual ~DomainProcessor();

		public: double* process(double* aData, unsigned int aLength, unsigned int aSamplePerRange, unsigned int aDomainIndex, unsigned int aRelativeDomainSfift, unsigned int aScaleDomainShift, bool aForwardDirection);

		private: void backShrink(double* aData, unsigned int aLength, unsigned int aRelativeDomainSfift, unsigned int aScaleDomainShift);
	};
}

#endif
