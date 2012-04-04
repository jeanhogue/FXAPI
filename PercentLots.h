#ifndef __PercentLots_H__
#define __PercentLots_H__

#include "TradingParameter.h"


// This is a lots calculator to make sure that only n% are 
// at risk on a given trade.
class PercentLots : public LotsParameter
{
public:
    PercentLots(double _percent);

    virtual double GetCurrentValue(double currentBalance, double stopLoss, double ask);

private:
    double percent;     // percent of current balance to risk in next trade
};

#endif