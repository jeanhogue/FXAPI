#ifndef __RandomDataGenerator_H__
#define __RandomDataGenerator_H__

#include "DataReader.h"


class RandomDataGenerator : public DataReader
{
public:
    RandomDataGenerator(double _startPrice, int _numBars);

    virtual double GetNextTick();

    virtual bool IsValidReader() { return true; }
    virtual bool EndOfData();

    virtual std::string GetStr() { return "Random Data Generator"; }

private:
    double startPrice;
    double range;
    int numBars;
    double momentum;
};


#endif