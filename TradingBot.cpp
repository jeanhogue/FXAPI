#include "TradingBot.h"
#include "Order.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Defs.h"


TradingBot::TradingBot(CapitalManager *_capitalManager, ObjectManager *_objectManager)
: capitalManager(_capitalManager), objectManager(_objectManager)
{
    takeProfit = PipsToPrice(50);
    stopLosses = PipsToPrice(20);
    lots = 0.1;
}

TradingBot::~TradingBot()
{
    for (unsigned int i = 0; i < indicators.size(); ++ i)
        delete indicators[i];
    indicators.clear();
}

void TradingBot::Buy(double price, int timeIndex)
{
    capitalManager->AddOrder(CreateOrder(tBUY, timeIndex, lots, price, price + takeProfit, price - stopLosses));
    objectManager->AddObject(new OrderBar(timeIndex, price, price + takeProfit, price - stopLosses));
}

void TradingBot::Sell(double price, int timeIndex)
{
    capitalManager->AddOrder(CreateOrder(tSELL, timeIndex, lots, price, price - takeProfit, price + stopLosses));
    objectManager->AddObject(new OrderBar(timeIndex, price, price - takeProfit, price + stopLosses));
}

void TradingBot::Render(int index, int numBarsToDraw, double minValue, double maxValue)
{
    for (unsigned int i = 0; i < indicators.size(); ++ i)
        indicators[i]->Render(index, numBarsToDraw, minValue, maxValue);
}