#ifndef WAVEFRACTAL_PARSER_H
#define WAVEFRACTAL_PARSER_H

#include <fstream>
#include <Windows.h>

#include "Data_chunks.h"


struct __FRACDESCR
{

    __FRACDESCR()
    {
        _chunkHead.id[0] = 'R';

        _chunkHead.id[1] = 'O';

        _chunkHead.id[2] = 'A';

        _chunkHead.id[3] = 'D';
    }

    bool operator == (const __FRACDESCR &arg)
    {
        return this->_chunkHead.id[0] == arg._chunkHead.id[0]
                && this->_chunkHead.id[1] == arg._chunkHead.id[1]
                && this->_chunkHead.id[2] == arg._chunkHead.id[2]
                && this->_chunkHead.id[3] == arg._chunkHead.id[3];
    }

        __WAVECHUNKHEAD _chunkHead;

        __FRACFORMAT _format;
};

struct __FRACMAP
{

    __FRACMAP()
    {
        _chunkHead.id[0] = 'M';

        _chunkHead.id[1] = 'A';

        _chunkHead.id[2] = 'P';

        _chunkHead.id[3] = ' ';

    }

    bool operator == (const __FRACMAP &arg)
    {
        return this->_chunkHead.id[0] == arg._chunkHead.id[0]
                && this->_chunkHead.id[1] == arg._chunkHead.id[1]
                && this->_chunkHead.id[2] == arg._chunkHead.id[2]
                && this->_chunkHead.id[3] == arg._chunkHead.id[3];
    }
        __WAVECHUNKHEAD _chunkHead;
};

struct __FRACDESCRINDECES
{

    __FRACDESCRINDECES()
    {
        _chunkHead.id[0] = 'F';

        _chunkHead.id[1] = 'I';

        _chunkHead.id[2] = 'N';

        _chunkHead.id[3] = 'D';

    }

    bool operator == (const __FRACDESCRINDECES &arg)
    {
        return this->_chunkHead.id[0] == arg._chunkHead.id[0]
                && this->_chunkHead.id[1] == arg._chunkHead.id[1]
                && this->_chunkHead.id[2] == arg._chunkHead.id[2]
                && this->_chunkHead.id[3] == arg._chunkHead.id[3];
    }
        __WAVECHUNKHEAD _chunkHead;
};


class WaveFractalFormatData
{
public:
    WaveFractalFormatData(){}

    WaveFractalFormatData(__WAVEDESCR aWavedescr,
                          __WAVEFORMAT aWaveformat,
                          __WAVEDESCRDATA aWavedescrdata,
                          int dataPos)
        : _wavedescr(aWavedescr),
          _waveformat(aWaveformat),
          _wavedescrdata(aWavedescrdata),
          _fractal(false),
          _dataPos(dataPos)
    {

    }

    WaveFractalFormatData(__WAVEDESCR aWavedescr,
                          __WAVEFORMAT aWaveformat,
                          __WAVEDESCRDATA aWavedescrdata,
                          int dataPos,
                          __FRACDESCR aFracdescr,
                          __FRACMAP aFractMap,
                          __FRACDESCRINDECES aFractDescrIndeces,
                          int aFractalMapPos,
                          int aFractDescrIndecesPos)
        : _wavedescr(aWavedescr),
          _waveformat(aWaveformat),
          _wavedescrdata(aWavedescrdata),
          _fractDescr(aFracdescr),
          _fractMap(aFractMap),
          _fractDescrIndeces(aFractDescrIndeces),
          _fractal(true),
          _dataPos(dataPos),
          _fractalMapPos(aFractalMapPos),
          _fractDescrIndecesPos(aFractDescrIndecesPos)
    {

    }

    bool isWaveFractal()
    {
        return _fractal;
    }

    __WAVEDESCR getWavedescr()
    {
        return _wavedescr;
    }

    __WAVEFORMAT getWaveformat()
    {
        return _waveformat;
    }

    __WAVEDESCRDATA getWavedescrdata()
    {
        return _wavedescrdata;
    }

    int getDataPos()
    {
        return _dataPos;
    }

    __FRACDESCR getFracdescr()
    {
        return _fractDescr;
    }

    __FRACMAP getFracmap()
    {
        return _fractMap;
    }

    __FRACDESCRINDECES getFracdescrindeces()
    {
        return _fractDescrIndeces;
    }

    int getFractalMapPos()
    {
        return _fractalMapPos;
    }

    int getFractalDescrIndecesPos()
    {
        return _fractDescrIndecesPos;
    }

private:

    __WAVEDESCR _wavedescr;

    __WAVEFORMAT _waveformat;

    __WAVEDESCRDATA _wavedescrdata;

    __FRACDESCR _fractDescr;

    __FRACMAP _fractMap;

    __FRACDESCRINDECES _fractDescrIndeces;

    bool _fractal;

    int _dataPos;

    int _fractalMapPos;

    int _fractDescrIndecesPos;

};


class WaveFractal_parser
{
public:

    static WaveFractal_parser &getInstance();

    WaveFractalFormatData parse(HANDLE hFile);

private:

    WaveFractal_parser();

    ~WaveFractal_parser();

    WaveFractal_parser(const WaveFractal_parser&);

    bool parseWaveDescr(HANDLE hFile, __WAVEDESCR &lWaveDescr);

    __WAVEFORMAT parseWaveFormat(HANDLE hFile, __WAVECHUNKHEAD aHead);

    void parseFractalFormat(HANDLE hFile, __FRACDESCR &lfractDescr);

};

#endif // WAVEFRACTAL_PARSER_H
