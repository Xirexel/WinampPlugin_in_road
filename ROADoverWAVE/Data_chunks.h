#ifndef DATA_CHUNKS_H
#define DATA_CHUNKS_H


typedef struct 
{
        char id[4];   // идентификатор типа файла
        unsigned int size;   // размер оставшейся части файла

} __WAVECHUNKHEAD;

typedef struct 
{
        __WAVECHUNKHEAD chunkHead;   // размер оставшейся части файла
        char wave[4];  // формат файла

} __WAVEDESCR;

typedef struct 
{
        __WAVECHUNKHEAD chunkHead;
        unsigned short format;     // аудио формат
        unsigned short channels;    // число каналов
        unsigned int sampleRate;    // частота дискретизации
        unsigned int byteRate;     // скорость потока
        unsigned short blockAlign;  // смещение блока выборки
        unsigned short bitsPerSample;   // разрядность выборки

} __WAVEFORMAT;

typedef struct 
{
        __WAVECHUNKHEAD chunkHead;
} __WAVEDESCRDATA;


typedef struct 
{
        unsigned int _format;
        unsigned int _superFrameLength;
        unsigned int _frameRangeLength;
        unsigned int _domainShift;
        unsigned int _domainShiftScale;
        unsigned int _originalAmountOfChannels;
        unsigned int _averDiffMode;
        unsigned int _encriptionCode;
} __FRACFORMAT;

#endif