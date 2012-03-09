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

void MovingAverage::OnNewBar(double sample)
{
    buffer[bufferIndex] = sample;
    bufferIndex ++;
    if (bufferIndex >= period)
        bufferIndex = 0;
}

double MovingAverage::GetValue()
{
    double sum = 0;
    for (int i = 0; i < period; ++ i)
        sum += buffer[i];
    return sum / period;
}