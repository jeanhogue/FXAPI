#include "TradingBot.h"
#include "Order.h"


TradingBot::TradingBot(CapitalManager *_capitalManager)
: capitalManager(_capitalManager)
{
}

void TradingBot::Buy(double price)
{
    capitalManager->AddOrder(CreateOrder(tBUY, 0.1, price, price + 0.0050, price - 0.0020));
}

void TradingBot::Sell(double price)
{
    capitalManager->AddOrder(CreateOrder(tSELL, 0.1, price, price + 0.0050, price - 0.0020));
}