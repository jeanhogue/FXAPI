#ifndef __RandomDataGenerator_H__
#define __RandomDataGenerator_H__

#include "DataReader.h"


class RandomDataGenerator : public DataReader
{
public:
    RandomDataGenerator(double _startPrice, int _numBars);

    virtual void Init();

    virtual double GetNextTick();

    virtual bool EndOfData();

private:
    double startPrice;
    double range;
    int numBars;
    double lastSample;
};


#endif