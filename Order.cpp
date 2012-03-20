#include <cassert>
#include "Order.h"


Order::Order(double _volume, double price, double _takeProfits, double _stopLoss)
: volume(_volume), openPrice(price), takeProfits(_takeProfits), stopLoss(_stopLoss), active(true)
{
}

/*
volume 1 = 100,000$

leverage 1:100 => to buy volume 1 (1 lot), need 1000$

1.2345 -> 1.2348 (3 pips) = 0.0003 * 100,000 * 1 = 30$
*/

double Order::GetProfits()
{
    return (closePrice - openPrice) * volume * 100000;
}


BuyOrder::BuyOrder(double volume, double price, double takeProfits, double stopLoss)
: Order(volume, price, takeProfits, stopLoss)
{
}

void BuyOrder::OnNewBar(double sample)
{
    // check if we reached take profit or stop loss values
    if (sample >= takeProfits || sample <= stopLoss)
    {
        closePrice = sample;
        active = false;
    }
}


SellOrder::SellOrder(double volume, double price, double takeProfits, double stopLoss)
: Order(volume, price, takeProfits, stopLoss)
{
}

void SellOrder::OnNewBar(double sample)
{
    // check if we reached take profit or stop loss values
    if (sample >= takeProfits || sample <= stopLoss)
    {
        closePrice = sample;
        active = false;
    }
}


Order *CreateOrder(OrderType type, double volume, double price, double takeProfits, double stopLoss)
{
    if (type == tBUY)
        return new BuyOrder(volume, price, takeProfits, stopLoss);
    else if (type == tSELL)
        return new SellOrder(volume, price, takeProfits, stopLoss);
    else
    {
        assert(0);
        return 0;
    }
}