#ifndef __DATAREADER_H__
#define __DATAREADER_H__

#include <string>
#include "Defs.h"


class DataReader
{
public:
    DataReader(Timeframe _timeFrame) : timeFrame(_timeFrame) {}

    virtual double GetNextTick() = 0;
  
    virtual bool IsValidReader() = 0;
    virtual bool EndOfData() = 0;

    virtual std::string GetStr() = 0;

protected:
    Timeframe timeFrame;
};

#endif