#include "TradingBot.h"
#include "Order.h"
#include "ObjectManager.h"
#include "Object.h"


TradingBot::TradingBot(CapitalManager *_capitalManager, ObjectManager *_objectManager)
: capitalManager(_capitalManager), objectManager(_objectManager)
{
}

void TradingBot::Buy(double price, int timeIndex)
{
    capitalManager->AddOrder(CreateOrder(tBUY, timeIndex, 0.1, price, price + 0.0050, price - 0.0020));
    objectManager->AddObject(new OrderBar(timeIndex, price, price + 0.0050, price - 0.0020));
    objectManager->AddObject(new TextObj("aaueu", timeIndex, price));
}

void TradingBot::Sell(double price, int timeIndex)
{
    capitalManager->AddOrder(CreateOrder(tSELL, timeIndex, 0.1, price, price - 0.0050, price + 0.0020));
    objectManager->AddObject(new OrderBar(timeIndex, price, price - 0.0050, price + 0.0020));
}