#ifndef __MovingAverage_H__
#define __MovingAverage_H__

#include "IFXActor.h"


class MovingAverage : public IFXActor
{
public:
    MovingAverage(int _period);

    virtual void Init();
    virtual void OnNewBar(double sample);

private:
    int period;
    double *buffer;
    int bufferIndex;
};


#endif