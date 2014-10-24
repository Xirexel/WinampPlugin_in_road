#ifndef IREADER_H
#define IREADER_H

class IReader
{
public:

    IReader()
    {}

    virtual ~IReader(){}

    virtual int readData(char *data, int maxlen)=0;

    virtual int getSampleAmount()=0;

    virtual void setPosition(int position)=0;

};

#endif // IREADER_H
