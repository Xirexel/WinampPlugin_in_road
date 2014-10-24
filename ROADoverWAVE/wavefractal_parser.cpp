#include "wavefractal_parser.h"


LONG GetFilePointer(HANDLE hFile)
{
   return SetFilePointer(hFile,0,0,FILE_CURRENT);
}

WaveFractal_parser::WaveFractal_parser()
{
}

WaveFractal_parser::~WaveFractal_parser()
{
}

WaveFractalFormatData WaveFractal_parser::parse(HANDLE hFile)
{
    bool result = false;

    WaveFractalFormatData lWaveFractalFormatData;

    do
    {
        __WAVEDESCR lWaveDescr;

        bool lIsWaveDescr = parseWaveDescr(hFile, lWaveDescr);

        if(!lIsWaveDescr)
            break;

        __WAVEDESCRDATA lWAVEDESCRDATA;

        __WAVEFORMAT lWAVEFORMAT;

        __WAVECHUNKHEAD lHead;

        int ldataPos = -1;

        int lfractalMapPos = -1;

        int lfractDescrIndecesPos = -1;

        __FRACDESCR lfractDescr;

        __FRACMAP lfractMap;

        __FRACDESCRINDECES lfractDescrIndeces;

		bool state = true;

        while(state)
        {
			DWORD nBytesRead;

			BOOL bResult = ReadFile(hFile, lHead.id, sizeof(lHead.id), &nBytesRead, NULL);
		
			if(bResult &&  nBytesRead == 0)
				break;

			bResult = ReadFile(hFile, &lHead.size, sizeof(lHead.id), &nBytesRead, NULL);
		
			if(bResult &&  nBytesRead == 0)
				break;
			
            if(lHead.id[0] == 'f'
                    && lHead.id[1] == 'm'
                    && lHead.id[2] == 't'
                    && lHead.id[3] == ' ')
            {
                __WAVEFORMAT lWaveFormat = parseWaveFormat(hFile, lHead);

                if(lWaveFormat.format != 1)
                    break;

                lWAVEFORMAT = lWaveFormat;

            }
            else if(lHead.id[0] == 'd'
                        && lHead.id[1] == 'a'
                        && lHead.id[2] == 't'
                        && lHead.id[3] == 'a')
            {
                result = true;

                lWAVEDESCRDATA.chunkHead = lHead;

                ldataPos = GetFilePointer(hFile);

                break;
            }
            else
			{
				DWORD dwPtr = SetFilePointer( hFile, 
                                lHead.size-1, 
                                NULL, 
                                FILE_CURRENT ); 

				if (dwPtr == INVALID_SET_FILE_POINTER)
					break;

			}

        }

        if(!result)
            break;

        int lpos = GetFilePointer(hFile);
		
		DWORD dwPtr = SetFilePointer( hFile, 
                                lHead.size, 
                                NULL, 
                                FILE_CURRENT ); 

		if (dwPtr == INVALID_SET_FILE_POINTER)
			break;

		int size = GetFileSize(hFile, NULL);


		
        if((lHead.size + lpos) >= size)
        {

            lWaveFractalFormatData = WaveFractalFormatData(lWaveDescr, lWAVEFORMAT,
                                             lWAVEDESCRDATA, ldataPos);
			
			DWORD dwPtr = SetFilePointer( hFile, 
                                lpos, 
                                NULL, 
                                FILE_BEGIN ); 

			if (dwPtr == INVALID_SET_FILE_POINTER)
				break;

            break;
        }

        result = false;

        int l = lpos + lHead.size - 1;

		
		dwPtr = SetFilePointer( hFile, 
                                lpos + lHead.size - 1, 
                                NULL, 
                                FILE_BEGIN ); 

		if (dwPtr == INVALID_SET_FILE_POINTER)
			break;
		
		DWORD nBytesRead;

		BOOL bResult = ReadFile(hFile, lfractDescr._chunkHead.id, sizeof(lfractDescr._chunkHead.id), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;
		
        __FRACDESCR ltest__FRACDESCR;

        if(!(lfractDescr == ltest__FRACDESCR))
        {
            break;
        }

		bResult = ReadFile(hFile, &lfractDescr._chunkHead.size, sizeof(lfractDescr._chunkHead.size), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;
		
        if(lfractDescr._chunkHead.size != sizeof(__FRACFORMAT))
            break;

        parseFractalFormat(hFile, lfractDescr);

//        (*stream) >> lfractDescr._format._format;

//        (*stream) >> lfractDescr._format._superFrameLength;

//        (*stream) >> lfractDescr._format._frameRangeLength;

//        (*stream) >> lfractDescr._format._domainShift;

//        (*stream) >> lfractDescr._format._domainShiftScale;

//        (*stream) >> lfractDescr._format._originalAmountOfChannels;

//        (*stream) >> lfractDescr._format._averDiffMode;

//        (*stream) >> lfractDescr._format._encriptionCode;

		

		bResult = ReadFile(hFile, lfractMap._chunkHead.id, sizeof(lfractMap._chunkHead.id), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;
		
        __FRACMAP ltemp__FRACMAP;

        if(!(lfractMap == ltemp__FRACMAP))
        {
            break;
        }
		
		bResult = ReadFile(hFile, &lfractMap._chunkHead.size, sizeof(lfractMap._chunkHead.size), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;
		

        lfractalMapPos = GetFilePointer(hFile);

//        stream->seekg(0, std::_S_end);

//        lfractalMapPos = stream->tellg();

//        unsigned int g = lfractMap._chunkHead.size;

		dwPtr = SetFilePointer( hFile, 
                                lfractMap._chunkHead.size, 
                                NULL, 
                                FILE_CURRENT ); 

		if (dwPtr == INVALID_SET_FILE_POINTER)
			break;
		
		bResult = ReadFile(hFile, lfractDescrIndeces._chunkHead.id, sizeof(lfractDescrIndeces._chunkHead.id), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;
		

        __FRACDESCRINDECES ltemp__FRACDESCRINDECES;

        if(!(lfractDescrIndeces == ltemp__FRACDESCRINDECES))
        {
            break;
        }
		
		bResult = ReadFile(hFile, &lfractDescrIndeces._chunkHead.size, sizeof(lfractDescrIndeces._chunkHead.size), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;
		
        lfractDescrIndecesPos = GetFilePointer(hFile);
		
        result = true;

        if(result)
            lWaveFractalFormatData = WaveFractalFormatData(lWaveDescr, lWAVEFORMAT,
                                                           lWAVEDESCRDATA, ldataPos, lfractDescr,
                                                           lfractMap, lfractDescrIndeces,
                                                           lfractalMapPos, lfractDescrIndecesPos);

    }
    while(false);

    return lWaveFractalFormatData;
}

WaveFractal_parser &WaveFractal_parser::getInstance()
{
    static WaveFractal_parser instance;

    return instance;
}

bool WaveFractal_parser::parseWaveDescr(HANDLE hFile, __WAVEDESCR &lWaveDescr)
{
    bool result = false;

    do
    {
		DWORD nBytesRead;

		BOOL bResult = ReadFile(hFile, lWaveDescr.chunkHead.id, sizeof(lWaveDescr.chunkHead.id), &nBytesRead, NULL);
		
		if(!bResult &&  nBytesRead == 0)
			break;

        if(nBytesRead != sizeof(lWaveDescr.chunkHead.id))
            break;

        if(lWaveDescr.chunkHead.id[0] != 'R'
                || lWaveDescr.chunkHead.id[1] != 'I'
                || lWaveDescr.chunkHead.id[2] != 'F'
                || lWaveDescr.chunkHead.id[3] != 'F')
            break;

		bResult = ReadFile(hFile, &lWaveDescr.chunkHead.size, sizeof(lWaveDescr.chunkHead.size), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

        if(nBytesRead != sizeof(lWaveDescr.chunkHead.id))
            break;

		bResult = ReadFile(hFile, lWaveDescr.wave, sizeof(lWaveDescr.wave), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;
		
        if(nBytesRead != sizeof(lWaveDescr.chunkHead.id))
            break;

        if(lWaveDescr.wave[0] != 'W'
                || lWaveDescr.wave[1] != 'A'
                || lWaveDescr.wave[2] != 'V'
                || lWaveDescr.wave[3] != 'E')
            break;

        result = true;
    }
    while(false);

    return result;
}

__WAVEFORMAT WaveFractal_parser::parseWaveFormat(HANDLE hFile, __WAVECHUNKHEAD aHead)
{
    bool result = false;

    __WAVEFORMAT lwavedescr;

    lwavedescr.format = -1;

    do
    {
		
		DWORD nBytesRead;

		BOOL bResult = ReadFile(hFile, &lwavedescr.format, sizeof(lwavedescr.format), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lwavedescr.channels, sizeof(lwavedescr.channels), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lwavedescr.sampleRate, sizeof(lwavedescr.sampleRate), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lwavedescr.byteRate, sizeof(lwavedescr.byteRate), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lwavedescr.blockAlign, sizeof(lwavedescr.blockAlign), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lwavedescr.bitsPerSample, sizeof(lwavedescr.bitsPerSample), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;
		
//        (*stream) >> lwavedescr.format;

//        (*stream) >> lwavedescr.channels;

//        (*stream) >> lwavedescr.sampleRate;

//        (*stream) >> lwavedescr.byteRate;

//        (*stream) >> lwavedescr.blockAlign;

//        (*stream) >> lwavedescr.bitsPerSample;

        int shift = aHead.size - 16;

		DWORD dwPtr = SetFilePointer( hFile, 
                                shift, 
                                NULL, 
                                FILE_CURRENT ); 

		if (dwPtr == INVALID_SET_FILE_POINTER)
			break;

        result = true;

    }
    while(false);

    lwavedescr.chunkHead = aHead;

    lwavedescr.chunkHead.size = 16;

    return lwavedescr;
}

void WaveFractal_parser::parseFractalFormat(HANDLE hFile, __FRACDESCR &lfractDescr)
{
	do
	{
		
		DWORD nBytesRead;

		BOOL bResult = ReadFile(hFile, &lfractDescr._format._format, sizeof(lfractDescr._format._format), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lfractDescr._format._superFrameLength, sizeof(lfractDescr._format._superFrameLength), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lfractDescr._format._frameRangeLength, sizeof(lfractDescr._format._frameRangeLength), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lfractDescr._format._domainShift, sizeof(lfractDescr._format._domainShift), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lfractDescr._format._domainShiftScale, sizeof(lfractDescr._format._domainShiftScale), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lfractDescr._format._originalAmountOfChannels, sizeof(lfractDescr._format._originalAmountOfChannels), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lfractDescr._format._averDiffMode, sizeof(lfractDescr._format._averDiffMode), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

		bResult = ReadFile(hFile, &lfractDescr._format._encriptionCode, sizeof(lfractDescr._format._encriptionCode), &nBytesRead, NULL);
		
		if(bResult &&  nBytesRead == 0)
			break;

	}
	while(false);

}
