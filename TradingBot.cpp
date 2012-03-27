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