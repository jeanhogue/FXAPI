#include "MovingAverage.h"
#include <cassert>
#include <memory>


MovingAverage::MovingAverage(int _period)
: period(_period)
{
    assert(period > 0 && period < 10000);
}

MovingAverage::~MovingAverage()
{
    delete [] buffer;
}

void MovingAverage::Init()
{
    buffer = new double[period];
    memset(buffer, 0, sizeof(double) * period);
    bufferIndex = 0;
}

void MovingAverage::OnNewBar(double sample, int timeIndex)
{
    buffer[bufferIndex] = sample;
    bufferIndex ++;
    if (bufferIndex >= period)
        bufferIndex = 0;

    values.push_back(GetValue());
}


SMA::SMA(int period) : MovingAverage(period) 
{}

double SMA::GetValue()
{
    double sum = 0;
    for (int i = 0; i < period; ++ i)
        sum += buffer[i];
    return sum / period;
}


EMA::EMA(int period) 
: MovingAverage(period), lastValue(0), a(2. / (period + 1)), oneMinusA(1 - a) 
{}

double EMA::GetValue()
{
    double mostRecentBar = 0;
    if (bufferIndex > 0)
        mostRecentBar = buffer[bufferIndex - 1];
    else
        mostRecentBar = buffer[period - 1];

    double newValue = a * mostRecentBar + oneMinusA * lastValue;
    lastValue = newValue;
    return newValue;
}


MovingAverage *CreateMA(MAType type, int period)
{
    if (type == tSMA)
        return new SMA(period);
    else if (type == tEMA)
        return new EMA(period);

    assert(0);
    return 0;
}