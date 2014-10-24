#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FractalDataContainer_h__
#define __FractalDataContainer_h__

// #include "IDoubleDataContainer.h"
// #include "IUCharDataContainer.h"
// #include "IUIntDataContainer.h"
#include "../ROAD/IFractalDataContainer.h"
#include "DoubleDataContainer.h"
#include "UCharDataContainer.h"
#include "UIntDataContainer.h"


namespace ROADdecoding
{
	class IDoubleDataContainer;
	class IUCharDataContainer;
	class IUIntDataContainer;
	class IFractalDataContainer;
}
namespace ROADover
{
	class DoubleDataContainer;
	class UCharDataContainer;
	class UIntDataContainer;
	class FractalDataContainer;
}

namespace ROADover
{
	class FractalDataContainer: public ROADdecoding::IFractalDataContainer
	{
		public: ROADover::DoubleDataContainer _averDataConatainer;
		public: ROADover::UCharDataContainer _inecesContainer;
		public: ROADover::UCharDataContainer _domainsConatiner;
		public: ROADover::UCharDataContainer _scalesContainer;
		public: ROADover::UIntDataContainer _lengthDataContainer;

		public: ROADdecoding::IDoubleDataContainer* getAver();

		public: ROADdecoding::IUCharDataContainer* getIndeces();

		public: ROADdecoding::IUCharDataContainer* getDomain();

		public: ROADdecoding::IUCharDataContainer* getScales();

		public: ROADdecoding::IUIntDataContainer* getLengths();

		public: FractalDataContainer(unsigned int aLength);
	};
}

#endif
