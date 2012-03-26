#ifndef __DATAREADER_H__
#define __DATAREADER_H__

#include <string>
#include <vector>
#include "Defs.h"


class DataReader
{
public:
    DataReader(Timeframe _timeFrame) : timeFrame(_timeFrame) {}

    virtual double GetNextTick() = 0;
  
    virtual bool IsValidReader() = 0;
    virtual bool EndOfData() = 0;

    virtual double GetSampleAtIndex(int n);

    virtual double GetMinValueInRange(int start, int end);
    virtual double GetMaxValueInRange(int start, int end);

    virtual int GetTimeIndex() { return timeIndex; }
    virtual std::string GetStr() = 0;

    void PushDataSample(double sample);

protected:
    Timeframe timeFrame;
    int timeIndex;
    std::vector<double> data;
};

#endif