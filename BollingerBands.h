#ifndef __BollingerBands_H__
#define __BollingerBands_H__

#include "IFXIndicator.h"


class MovingAverage;

class BollingerBands : public IFXIndicator
{
public:
    BollingerBands(int _period, float _D);
    ~BollingerBands();

    virtual void Init();
    virtual void OnNewBar(double sample, int timeIndex);

    virtual void Render(int index, int numBarsToDraw, double minValue, double maxValue);

private:
    MovingAverage *movingAverage;

    int period;
    float D;
    double *buffer;

    std::vector<double> BB;
};


#endif