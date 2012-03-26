#ifndef __TradingBot_H__
#define __TradingBot_H__

#include <vector>
#include "IFXActor.h"
#include "IFXIndicator.h"
#include "CapitalManager.h"


class ObjectManager;

class TradingBot : public IFXActor
{
public:
    TradingBot(CapitalManager *_capitalManager, ObjectManager *_objectManager);

    void Buy(double price, int timeIndex);
    void Sell(double price, int timeIndex);

    virtual bool IsTrader() { return true; }

    std::vector<IFXIndicator *> GetIndicators() { return indicators; }

protected:
    CapitalManager *capitalManager;
    ObjectManager *objectManager;

    std::vector<IFXIndicator *> indicators;
};

#endif