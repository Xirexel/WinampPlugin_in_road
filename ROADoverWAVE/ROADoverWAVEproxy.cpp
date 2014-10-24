#include <fstream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "ROADoverWAVEproxy.h"
#include "wavefractal_parser.h"
#include "../ROADover/ROADoverDecodingOptions.h"
#include "../ROADoverWAVE/roadoverwave.h"



void release(IReader *ptrIReader) 
{ 
	if(ptrIReader != NULL)
		delete ptrIReader;
}

int readData(char *ptrData, int maxlen, IReader *ptrIReader)
{
	int length = ptrIReader->readData(ptrData, maxlen);

	return length;
}

int getDurationLength(IReader *ptrIReader, int sampleRate)
{
	float lAmountLength = ptrIReader->getSampleAmount();

	float t = lAmountLength/(float)sampleRate;

	int lDurationLength = (t * 1000.0);

	return lDurationLength;
}

void setPosition(int position, IReader *ptrIReader)
{
	ptrIReader->setPosition(position);

}

int openFile(const wchar_t *filePath, int samplesPerRang, __FRACFORMAT lFractDescr, int originalBitsPerSample, int newBitsPerSample, IReader **_ptrIReader)
{
	int result = 0;

	do
	{
		HANDLE hFile;
				
		hFile = CreateFile(filePath,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

		if (hFile == INVALID_HANDLE_VALUE) 
		{ 
			break;
		}
		
        WaveFractalFormatData _waveFractalFormatData = WaveFractal_parser::getInstance().parse(hFile);

        CloseHandle(hFile);

		ROADover::ROADoverDecodingOptions options;

		options.setAmountOfChannels(_waveFractalFormatData.getFracdescr()._format._originalAmountOfChannels);

        options.setFrameRangLength(_waveFractalFormatData.getFracdescr()._format._frameRangeLength);


		ROADover::MixingChannelsMode lMixingChannelMode = ROADover::NONE;
		
        switch(_waveFractalFormatData.getFracdescr()._format._averDiffMode)
        {
        case 0:
        default:
            lMixingChannelMode = ROADover::LplusR;
            break;

        case 1:
            lMixingChannelMode = ROADover::LminusR;
            break;

        case 2:
            lMixingChannelMode = ROADover::NONE;
            break;

        }



        options.setMixingChannelsMode(lMixingChannelMode);

        options.setRelativeDomainShift(_waveFractalFormatData.getFracdescr()._format._domainShift);

        options.setSamplesPerRang(samplesPerRang);

        options.setSuperframeLength(_waveFractalFormatData.getFracdescr()._format._superFrameLength);

        options.setScaleDomainShift(_waveFractalFormatData.getFracdescr()._format._domainShiftScale);

        options.setBitsPerSample(originalBitsPerSample);


        switch(originalBitsPerSample)
        {

        case 8:
            *_ptrIReader = new ROADoverWAVE<unsigned char, unsigned char>(options, _waveFractalFormatData, filePath);
            break;

        case 16:

            switch(newBitsPerSample)
            {
            case 16:
            default:
                *_ptrIReader = new ROADoverWAVE<short, short>( options,_waveFractalFormatData, filePath);
                break;
            case 32:
                *_ptrIReader = new ROADoverWAVE<short, int>( options,_waveFractalFormatData, filePath);

                break;
            }


            break;

        case 32:
            *_ptrIReader = new ROADoverWAVE<int, int>( options,_waveFractalFormatData, filePath);
            break;

        default:
            _ptrIReader = 0;
            break;
        }	

	}
	while(0);
	
	return result;
}


EXTERNC ROADoverWAVEproxy getROADoverWAVEproxy(const wchar_t *ptrFilePath)
{

	int isFractalCompression = 0;

	__WAVEFORMAT lWAVEFORMAT;

	__FRACFORMAT lFRACFORMAT;
	
    do
    {
		HANDLE hFile;
				
		hFile = CreateFile(ptrFilePath,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

		if (hFile == INVALID_HANDLE_VALUE) 
		{ 
			break;
		}
		
        WaveFractalFormatData lWaveFractalFormatData = WaveFractal_parser::getInstance().parse(hFile);

        CloseHandle(hFile);

        lWAVEFORMAT = lWaveFractalFormatData.getWaveformat();

		lFRACFORMAT = lWaveFractalFormatData.getFracdescr()._format;
		
        if(!lWaveFractalFormatData.isWaveFractal())
            break;
				
        if(lWAVEFORMAT.format == 0)
            break;

		isFractalCompression = 1;
    }
    while(false);

	ROADoverWAVEproxy g =
	{
		0,

		isFractalCompression,

		lWAVEFORMAT.format,

		lWAVEFORMAT.channels,

		lWAVEFORMAT.sampleRate,

		lWAVEFORMAT.byteRate,

		lWAVEFORMAT.blockAlign,

		lWAVEFORMAT.bitsPerSample,

		lFRACFORMAT,

		openFile,
		
		getDurationLength,
		
		readData,

		setPosition,

		release
	};
	

    return g;
}