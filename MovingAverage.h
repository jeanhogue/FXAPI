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

    virtual double GetValue();

private:
    int period;
    double *buffer;
    int bufferIndex;
};


#endif