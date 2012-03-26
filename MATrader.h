#ifndef __MATRADER_H__
#define __MATRADER_H__

#include "TradingBot.h"


class MovingAverage;

class MATrader : public TradingBot
{
public:
    MATrader(CapitalManager *capitalManager, ObjectManager *objectManager);

    virtual void Init();
    virtual void OnNewBar(double sample);

private:
    int GetState();

    MovingAverage *slowMA;
    MovingAverage *fastMA;

    int state;                              // 1 if fast is above slow, -1 if fast is below slow
    int barCount;
    static const int INIT_PERIOD = 20;      // for 20 bars, we don't generate any signal
};

#endif