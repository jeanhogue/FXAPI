#ifndef __TradingBot_H__
#define __TradingBot_H__

#include <vector>
#include "IFXActor.h"
#include "TradingParameter.h"
#include "IFXIndicator.h"
#include "CapitalManager.h"


class ObjectManager;

class TradingBot : public IFXActor, public Optimizable
{
public:
    TradingBot(CapitalManager *_capitalManager, ObjectManager *_objectManager);
    ~TradingBot();

    void Cleanup();

    void Buy(double price, int timeIndex);
    void Sell(double price, int timeIndex);

    virtual void Render(int index, int numBarsToDraw, double minValue, double maxValue);

    virtual bool IsTrader() { return true; }

protected:
    CapitalManager *capitalManager;
    ObjectManager *objectManager;

    TradingParameter *takeProfit;
    TradingParameter *stopLosses;
    LotsParameter *lots;

    std::vector<IFXActor *> indicators;
};

#endif