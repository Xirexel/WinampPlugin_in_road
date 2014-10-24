#ifndef ROADOVERWAVE_H
#define ROADOVERWAVE_H

//#include <fstream>
#include <limits>
//#include <QString>


#include "../ROADover/AROADover.h"
#include "IReader.h"
#include "wavefractal_parser.h"
#include "../ROADover/IRawDataBuffer.h"




template<class T, class O>
class ROADoverWAVE: public ROADover::AROADover, public IReader
{

public:

    ROADoverWAVE(ROADover::ROADoverDecodingOptions aOptions,
                 WaveFractalFormatData waveFractalFormatData,
                 const wchar_t *filePath)
        : ROADover::AROADover(aOptions),
          _sampleScale(1),
          _waveFractalFormatData(waveFractalFormatData),
          _pos(0),
          _nextPos(0),
          _readSize(0),
          _pData(new char[aOptions.getAmountOfChannels() * sizeof(typeOutSample) *
        aOptions.getSuperframeLength() * aOptions.getFrameRangLength() * aOptions.getSamplesPerRang()]),
          _lastLength(0)
    {		


		{
			std::numeric_limits<typeOutSample> lim; 

			maxValue = lim.max();

			minValue = lim.min();
		}

				
		hFile = CreateFile(filePath,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

		if (hFile == INVALID_HANDLE_VALUE) 
		{ 
			return;
		}

        _sampleScale = 1 << ((sizeof(typeOutSample) * 8)-(sizeof(typeInSample)*8));

        _waveFormat = _waveFractalFormatData.getWaveformat();

        _wavedescrdata = _waveFractalFormatData.getWavedescrdata();

		_amountSuperFrames = (_wavedescrdata.chunkHead.size / _waveFormat.blockAlign) / (aOptions.getSuperframeLength() * aOptions.getFrameRangLength());

        _sampleAmount = (_wavedescrdata.chunkHead.size / _waveFormat.blockAlign) * _options.getSamplesPerRang();

		_fractalIndecesLength = _waveFractalFormatData.getFracdescrindeces()._chunkHead.size;

        _offsetWaveData = _waveFractalFormatData.getDataPos();

        _offsetFractalMap = _waveFractalFormatData.getFractalMapPos();

        _offsetFractalIndeces = _waveFractalFormatData.getFractalDescrIndecesPos();

        this->_superFrameStep = _options.getSuperframeLength() * _options.getFrameRangLength() * _options.getSamplesPerRang();

        _superFrameLength = _options.getSuperframeLength() * _options.getFrameRangLength();

        _superFrameByteSize = _options.getSuperframeLength() * _options.getFrameRangLength() * _options.getSamplesPerRang() * _options.getAmountOfChannels() * sizeof(typeInSample)* (sizeof(typeOutSample)/sizeof(typeInSample));

        _blockAlign = _options.getAmountOfChannels() * sizeof(typeOutSample);

        _readSize = _superFrameByteSize;

        _lastLength = 0;

    }

    virtual ~ROADoverWAVE()
    {
        CloseHandle(hFile);

        delete []_pData;
    }

    virtual int readData(char *data, int maxlen)
    {
		if (_lastLength == 0)
		{
			int result = decode();

			if (result == -1)
				return result;

			_lastLength = _superFrameByteSize;
		}

        int lReadLength = maxlen;

        if(_lastLength > maxlen)
        {
            memcpy(data, _pData + (_superFrameByteSize - _lastLength), maxlen);

            _lastLength -= maxlen;
        }
        else
        {
            memcpy(data, _pData + (_superFrameByteSize - _lastLength), _lastLength);

            lReadLength = _lastLength;

            _lastLength = 0;
        }


        return lReadLength;
    }

    virtual int getSampleAmount()
    {
        return _sampleAmount;
    }

    virtual void setPosition(int position)
    {
		int lNumSuperFrame = position / this->_superFrameStep;

		this->_nextPos = lNumSuperFrame * this->_superFrameStep;
    }

    int decode()
    {
		return doOneDecoding();
    }



public: virtual int64 readROADdata(char* aData)
    {
        int64 lNumSuperFrame = this->_nextPos / this->_superFrameStep;

		if (lNumSuperFrame >= _amountSuperFrames)
			return -1;
		

        //fseek(_pFile, _offsetFractalMap - 1 + lNumSuperFrame * sizeof(int64), SEEK_SET);

		DWORD dwPtr = SetFilePointer( hFile, 
                                _offsetFractalMap + lNumSuperFrame * sizeof(int64), 
                                NULL, 
                                FILE_BEGIN ); 

			if (dwPtr == INVALID_SET_FILE_POINTER)
				return -1;
			
        int64 lFractalIndecesShift = 0;

        int64 lFractalIndecesShiftNext = 0;

        int64 lFractalIndecesLength = 0;

		
		DWORD nBytesRead;

		BOOL bResult = ReadFile(hFile, &lFractalIndecesShift, sizeof(lFractalIndecesShift), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			return -1;

        //fread(&lFractalIndecesShift, sizeof(lFractalIndecesShift), 1,_pFile);


		if (lNumSuperFrame == _amountSuperFrames - 1)
		{
			lFractalIndecesShiftNext = _fractalIndecesLength;
		}
		else
		{
			bResult = ReadFile(hFile, &lFractalIndecesShiftNext, sizeof(lFractalIndecesShiftNext), &nBytesRead, NULL);

			if (bResult &&  nBytesRead == 0)
				return -1;
		}


        //fread(&lFractalIndecesShiftNext, sizeof(lFractalIndecesShiftNext), 1,_pFile);


        lFractalIndecesLength = lFractalIndecesShiftNext - lFractalIndecesShift;

        //fseek(_pFile, _offsetFractalIndeces + lFractalIndecesShift, SEEK_SET);

		dwPtr = SetFilePointer( hFile, 
                                _offsetFractalIndeces + lFractalIndecesShift, 
                                NULL, 
                                FILE_BEGIN ); 

			if (dwPtr == INVALID_SET_FILE_POINTER)
				return -1;


//        fread(g, 1, 4,_pFile);

//        fread(&h, sizeof(h), 1,_pFile);


//        fread(aData, 1, lFractalIndecesLength,_pFile);

		bResult = ReadFile(hFile, aData, lFractalIndecesLength, &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			return -1;

//        qDebug(QString("lNumSuperFrame: %1").arg(lNumSuperFrame).toStdString().c_str());

        return lFractalIndecesLength;
    }

public: virtual unsigned int readAver(double* aData)
    {
        int result = 0;

        long lNumSuperFrame = this->_nextPos / this->_superFrameStep;

        //fseek(_pFile, _offsetWaveData + lNumSuperFrame * _superFrameLength * sizeof(typeInSample), SEEK_SET);

		
		DWORD dwPtr = SetFilePointer( hFile, 
                                _offsetWaveData + lNumSuperFrame * _superFrameLength * sizeof(typeInSample), 
                                NULL, 
                                FILE_BEGIN ); 

			if (dwPtr == INVALID_SET_FILE_POINTER)
				return 0;

        typeInSample laver;

        int lLength = _superFrameLength;

		DWORD nBytesRead;


        while(lLength > 0)
        {
			

			BOOL bResult = ReadFile(hFile, &laver, sizeof(laver), &nBytesRead, NULL);
		
			if(bResult &&  nBytesRead == 0)
				return 0;

            //fread(&laver, 1, sizeof(laver),_pFile);

            *aData = laver * _sampleScale;

            ++aData;

            --lLength;
        }

        this->_nextPos = lNumSuperFrame * this->_superFrameStep;

        result = _superFrameLength;



        return result;
    }

public: virtual unsigned int convertByteArrayIntoDoubleArray(const char* aByteData, unsigned int aLengthByteArray, double* aDoubleData)
    {
        typeInSample laver;

        int llaverLength = sizeof(typeInSample);

        unsigned int lcount = aLengthByteArray/llaverLength;

        for(unsigned int lIndex = 0;
            lIndex < lcount;
            ++lIndex)
        {
            memcpy(&laver, aByteData, llaverLength);

            aByteData+=llaverLength;

            aDoubleData[lIndex] = laver * _sampleScale;
        }

        return lcount;
    }

public: virtual void writeRawData(ROADover::IRawDataBuffer* aRawDataBuffer)
    {
        unsigned int lchannels = aRawDataBuffer->getCount();

        unsigned int lLength = aRawDataBuffer->getLength();

        typeOutSample lvalue;

        double lDoubleValue;

        int valueLength = sizeof(lvalue);

        char *lData = _pData;

        for(unsigned int lPosition = 0;
            lPosition < lLength;
            ++lPosition)
        {

            for(unsigned int lIndex = 0;
                lIndex < lchannels;
                ++lIndex)
            {

                ROADdecoding::IDoubleDataBuffer* lptrIDoubleDataBuffer = aRawDataBuffer->getIDoubleDataBuffer(lIndex);

                double * lptrData = lptrIDoubleDataBuffer->getData();

                lDoubleValue = lptrData[lPosition];

                if(lDoubleValue > maxValue)
                {
                    lDoubleValue = maxValue;
                }
                else if(lDoubleValue < minValue)
                {
                    lDoubleValue = minValue;
                }

                lvalue = lDoubleValue;

                memcpy(lData, &lvalue, valueLength);

                lData+=valueLength;

            }
        }

        long lNumSuperFrame = this->_nextPos / this->_superFrameStep;

        this->_nextPos = ++lNumSuperFrame * this->_superFrameStep;
    }

private:

    typedef T typeInSample;

    typedef O typeOutSample;

    double maxValue;

    double minValue;

    int _sampleScale;

    WaveFractalFormatData _waveFractalFormatData;

    __WAVEFORMAT _waveFormat;

    __WAVEDESCRDATA _wavedescrdata;

    int _sampleAmount;

	int _amountSuperFrames;

    int _pos;

    int _nextPos;

    int _offsetWaveData;

    int _offsetFractalMap;

    int _offsetFractalIndeces;

    int _superFrameStep;

    int _superFrameLength;

    int _superFrameByteSize;

    int _readSize;

    int _blockAlign;

	HANDLE hFile;

    char *_pData;

    int _lastLength;

	int64 _fractalIndecesLength;
};

#endif // ROADOVERWAVE_H
