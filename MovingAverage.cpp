#include "MovingAverage.h"
#include <cassert>
#include <memory>


MovingAverage::MovingAverage(int _period)
: period(_period)
{
    assert(period > 0 && period < 10000);
}

SMA::SMA(int period) : MovingAverage(period), buffer(0)
{}

SMA::~SMA()
{
    if (buffer)
        delete [] buffer;
}

void SMA::Init()
{
    buffer = new double[period];
    memset(buffer, 0, sizeof(double) * period);
    bufferIndex = 0;
    firstSample = true;
}

void SMA::OnNewBar(double sample, int timeIndex)
{
    if (firstSample)
    {
        for (int i = 0; i < period; ++ i)
            buffer[i] = sample;
        firstSample = false;
    }
    else
    {
        buffer[bufferIndex] = sample;
    }

    bufferIndex ++;
    if (bufferIndex >= period)
        bufferIndex = 0;

    values.push_back(GetMAValue());
}

double SMA::GetMAValue()
{
    double sum = 0;
    for (int i = 0; i < period; ++ i)
        sum += buffer[i];
    return sum / period;
}


EMA::EMA(int period) 
: MovingAverage(period), lastValue(0), a(2. / (period + 1)), oneMinusA(1 - a) 
{}

void EMA::Init()
{
    firstSample = true;
}

void EMA::OnNewBar(double _sample, int timeIndex)
{
    if (firstSample)
    {
        lastValue = _sample;
        firstSample = false;
    }
    
    sample = _sample;

    values.push_back(GetMAValue());
}

double EMA::GetMAValue()
{
    double newValue = a * sample + oneMinusA * lastValue;
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