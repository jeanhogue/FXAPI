#ifndef __TradingBot_H__
#define __TradingBot_H__

#include <vector>
#include "IFXActor.h"
#include "IFXIndicator.h"
#include "CapitalManager.h"


class TradingBot : public IFXActor
{
public:
    TradingBot(CapitalManager *_capitalManager);

    void Buy(double price);
    void Sell(double price);

    virtual bool IsTrader() { return true; }

    std::vector<IFXIndicator *> GetIndicators() { return indicators; }

protected:
    CapitalManager *capitalManager;

    std::vector<IFXIndicator *> indicators;
};

#endif