#ifndef __RandomDataGenerator_H__
#define __RandomDataGenerator_H__

#include "DataReader.h"


class RandomDataGenerator : public DataReader
{
public:
    RandomDataGenerator(double _startPrice, int _numBars, int _seed);

    virtual void Init();

    virtual double GetNextTick();

    virtual bool EndOfData();

private:
    double startPrice;
    double lastSample;
    int numBars;
    int seed;
};


#endif