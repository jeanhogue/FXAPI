#include "MovingAverage.h"
#include <cassert>
#include <memory>


MovingAverage::MovingAverage(int _period)
: period(_period)
{
    assert(period > 0 && period < 10000);
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