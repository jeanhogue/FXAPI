#include <cassert>
#include "Order.h"
#include "Object.h"


Order::Order(int _timeIndex, double _volume, double price, double _takeProfits, double _stopLoss)
: timeIndex(_timeIndex), volume(_volume), openPrice(price), takeProfits(_takeProfits), stopLoss(_stopLoss), active(true)
{
}

void Order::SetOrderBar(OrderBar *_bar) 
{ 
    bar = _bar; 
}

void Order::CloseOrder(double sample)
{
    closePrice = sample;
    active = false; 
}


BuyOrder::BuyOrder(int timeIndex, double volume, double price, double takeProfits, double stopLoss)
: Order(timeIndex, volume, price, takeProfits, stopLoss)
{
}

void BuyOrder::OnNewBar(double sample)
{
    // check if we reached take profit or stop loss values
    if (sample >= takeProfits || sample <= stopLoss)
    {
        closePrice = sample;
        active = false;

        if (closePrice > openPrice)
            bar->SetColor(0, 255, 0);
        else
            bar->SetColor(255, 0, 0);
    }
}

/*
volume 1 = 100,000$

leverage 1:100 => to buy volume 1 (1 lot), need 1000$

1.2345 -> 1.2348 (3 pips) = 0.0003 * 100,000 * 1 = 30$
*/

double BuyOrder::GetProfits()
{
    return (closePrice - openPrice) * volume * 100000;
}


SellOrder::SellOrder(int timeIndex, double volume, double price, double takeProfits, double stopLoss)
: Order(timeIndex, volume, price, takeProfits, stopLoss)
{
}

void SellOrder::OnNewBar(double sample)
{
    // check if we reached take profit or stop loss values
    if (sample <= takeProfits || sample >= stopLoss)
    {
        closePrice = sample;
        active = false;

        if (closePrice < openPrice)
            bar->SetColor(0, 255, 0);
        else
            bar->SetColor(255, 0, 0);
    }
}

double SellOrder::GetProfits()
{
    return (openPrice - closePrice) * volume * 100000;
}


Order *CreateOrder(OrderType type, int timeIndex, double volume, double price, double takeProfits, double stopLoss)
{
    if (type == tBUY)
        return new BuyOrder(timeIndex, volume, price, takeProfits, stopLoss);
    else if (type == tSELL)
        return new SellOrder(timeIndex, volume, price, takeProfits, stopLoss);
    else
    {
        assert(0);
        return 0;
    }
}