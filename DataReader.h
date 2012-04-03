#ifndef __DATAREADER_H__
#define __DATAREADER_H__

#include <string>
#include <vector>
#include "Defs.h"


class DataReader
{
public:
    DataReader(Timeframe _timeFrame) : timeFrame(_timeFrame) {}

    virtual void Init() = 0;
    virtual void Cleanup() { data.clear(); }

    virtual double GetNextTick() = 0;
  
    virtual bool EndOfData() = 0;

    virtual double GetSampleAtIndex(int n);

    virtual double GetMinValueInRange(int start, int end);
    virtual double GetMaxValueInRange(int start, int end);

    virtual int GetTimeIndex() { return timeIndex; }

    int GetBarCount() { return (int)data.size(); }
    void PushDataSample(double sample);

protected:
    Timeframe timeFrame;
    int timeIndex;
    std::vector<double> data;
};

#endif