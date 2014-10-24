#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __ROADdataBuffer_h__
#define __ROADdataBuffer_h__

namespace ROADover
{
	class ROADdataBuffer;
}

namespace ROADover
{
	class ROADdataBuffer
	{
		private: char* _data;

		public: ROADdataBuffer(unsigned int aLength);

        public: virtual ~ROADdataBuffer();

		public: char* getData();
	};
}

#endif
