
#ifndef ROADOVERWAVE
#define ROADOVERWAVE

#include "Data_chunks.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#include "IReader.h"
#else
typedef struct IReader IReader;
#define EXTERNC
#endif

typedef struct  
{
	IReader *_ptrIReader;

	int isFractalCompression;

	int format;     
    int channels;    
    int sampleRate;   
    int byteRate;     
    int blockAlign;  
    int bitsPerSample;   

	__FRACFORMAT fractalFormat;

	int(*openFile)(const wchar_t *filePath, int samplesPerRang, __FRACFORMAT lFractDescr, int originalBitsPerSample, int newBitsPerSample, IReader **_ptrIReader);

	int(*getDurationLength)(IReader *ptrIReader, int sampleRate);

	int(*readData)(char *ptrData, int maxlen, IReader *ptrIReader);

	void(*setPosition)(int position, IReader *ptrIReader);

	void(*release)(IReader *ptrIReader);

		
} ROADoverWAVEproxy;


EXTERNC ROADoverWAVEproxy getROADoverWAVEproxy(const wchar_t *filePath);

#endif