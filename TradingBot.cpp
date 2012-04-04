#include "TradingBot.h"
#include "Order.h"
#include "ObjectManager.h"
#include "Object.h"
#include "PercentLots.h"
#include "Defs.h"


TradingBot::TradingBot(CapitalManager *_capitalManager, ObjectManager *_objectManager)
: capitalManager(_capitalManager), objectManager(_objectManager)
{
    /*takeProfit = AddTradingParameter("Take Profit", PipsToPrice(20), PipsToPrice(100), PipsToPrice(10));
    stopLosses = AddTradingParameter("Stop Losses", PipsToPrice(15), PipsToPrice(50), PipsToPrice(10));
    lots = AddTradingParameter("Lots", 0.05, 0.5, 0.1);*/

    takeProfit = AddTradingParameter("Take Profit", PipsToPrice(60), PipsToPrice(100), PipsToPrice(10));
    stopLosses = AddTradingParameter("Stop Losses", PipsToPrice(45), PipsToPrice(50), PipsToPrice(10));
    
    lots = AddLotsParameter("Lots", 0.05, 0.5, 0.1);
    //lots = new PercentLots(0.01);
}

TradingBot::~TradingBot()
{
    Cleanup();
}

void TradingBot::Cleanup()
{
    for (unsigned int i = 0; i < indicators.size(); ++ i)
        delete indicators[i];
    indicators.clear();

    if (dynamic_cast<PercentLots *>(lots))
        delete lots;
}

void TradingBot::Buy(double price, int timeIndex)
{
    double dLots = lots->GetCurrentValue(capitalManager->GetFunds(), PriceToPips(stopLosses->GetCurrentValue()), price);
    double dTakeProfit = price + takeProfit->GetCurrentValue();
    double dStopLosses = price - stopLosses->GetCurrentValue();

    Order *order = CreateOrder(tBUY, timeIndex, dLots, price, dTakeProfit, dStopLosses);
    capitalManager->AddOrder(order);

    OrderBar *bar = new OrderBar(timeIndex, price, dTakeProfit, dStopLosses);
    objectManager->AddObject(bar);

    order->SetOrderBar(bar);
}

void TradingBot::Sell(double price, int timeIndex)
{
    double dLots = lots->GetCurrentValue(capitalManager->GetFunds(), PriceToPips(stopLosses->GetCurrentValue()), price);
    double dTakeProfit = price - takeProfit->GetCurrentValue();
    double dStopLosses = price + stopLosses->GetCurrentValue();

    Order *order = CreateOrder(tSELL, timeIndex, dLots, price, dTakeProfit, dStopLosses);
    capitalManager->AddOrder(order);

    OrderBar *bar = new OrderBar(timeIndex, price, dTakeProfit, dStopLosses);
    objectManager->AddObject(bar);

    order->SetOrderBar(bar);
}

void TradingBot::Render(int index, int numBarsToDraw, double minValue, double maxValue)
{
    for (unsigned int i = 0; i < indicators.size(); ++ i)
        indicators[i]->Render(index, numBarsToDraw, minValue, maxValue);
}