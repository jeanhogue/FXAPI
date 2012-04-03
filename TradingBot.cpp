#include "TradingBot.h"
#include "Order.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Defs.h"


TradingBot::TradingBot(CapitalManager *_capitalManager, ObjectManager *_objectManager)
: capitalManager(_capitalManager), objectManager(_objectManager)
{
    /*takeProfit = AddTradingParameter("Take Profit", PipsToPrice(20), PipsToPrice(100), PipsToPrice(10));
    stopLosses = AddTradingParameter("Stop Losses", PipsToPrice(15), PipsToPrice(50), PipsToPrice(10));
    lots = AddTradingParameter("Lots", 0.05, 0.5, 0.1);*/

    takeProfit = AddTradingParameter("Take Profit", PipsToPrice(60), PipsToPrice(100), PipsToPrice(10));
    stopLosses = AddTradingParameter("Stop Losses", PipsToPrice(45), PipsToPrice(50), PipsToPrice(10));
    lots = AddTradingParameter("Lots", 0.45, 0.5, 0.1);
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
}

void TradingBot::Buy(double price, int timeIndex)
{
    Order *order = CreateOrder(tBUY, timeIndex, lots->GetCurrentValue(), price, price + takeProfit->GetCurrentValue(), price - stopLosses->GetCurrentValue());
    capitalManager->AddOrder(order);

    OrderBar *bar = new OrderBar(timeIndex, price, price + takeProfit->GetCurrentValue(), price - stopLosses->GetCurrentValue());
    objectManager->AddObject(bar);

    order->SetOrderBar(bar);
}

void TradingBot::Sell(double price, int timeIndex)
{
    Order *order = CreateOrder(tSELL, timeIndex, lots->GetCurrentValue(), price, price - takeProfit->GetCurrentValue(), price + stopLosses->GetCurrentValue());
    capitalManager->AddOrder(order);

    OrderBar *bar = new OrderBar(timeIndex, price, price - takeProfit->GetCurrentValue(), price + stopLosses->GetCurrentValue());
    objectManager->AddObject(bar);

    order->SetOrderBar(bar);
}

void TradingBot::Render(int index, int numBarsToDraw, double minValue, double maxValue)
{
    for (unsigned int i = 0; i < indicators.size(); ++ i)
        indicators[i]->Render(index, numBarsToDraw, minValue, maxValue);
}