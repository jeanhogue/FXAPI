#ifndef __MovingAverage_H__
#define __MovingAverage_H__

#include "IFXIndicator.h"


class MovingAverage : public IFXIndicator
{
public:
    MovingAverage(int _period);
    ~MovingAverage();

    virtual void Init();
    virtual void OnNewBar(double sample);

protected:
    int period;
    double *buffer;
    int bufferIndex;
};


class SMA : public MovingAverage
{
public:
    SMA(int period);

    virtual double GetValue();
};


class EMA : public MovingAverage
{
public:
    EMA(int period);

    virtual double GetValue();

private:
    double a;               // a constant in the EMA formula
    double oneMinusA;       // (1 - a)
    double lastValue;
};


enum MAType
{
    tSMA,
    tEMA,
};

// factory method to create MAs
MovingAverage *CreateMA(MAType type, int period);

#endif