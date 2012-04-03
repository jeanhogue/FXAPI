#ifndef __MovingAverage_H__
#define __MovingAverage_H__

#include "IFXIndicator.h"


class MovingAverage : public IFXIndicator
{
public:
    MovingAverage(int _period);
    virtual ~MovingAverage() {}

protected:
    int period;
    bool firstSample;
};


class SMA : public MovingAverage
{
public:
    SMA(int period);
    ~SMA();

    virtual void Init();
    virtual void OnNewBar(double sample, int timeIndex);

protected:
    virtual double GetMAValue();

private:
    double *buffer;
    int bufferIndex;
};


class EMA : public MovingAverage
{
public:
    EMA(int period);

    virtual void Init();
    virtual void OnNewBar(double sample, int timeIndex);

protected:
    virtual double GetMAValue();

private:
    double a;               // a constant in the EMA formula
    double oneMinusA;       // (1 - a)
    double sample;
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