#ifndef __Order_H__
#define __Order_H__


class Order
{
public:
    Order(double _volume, double price, double _takeProfits, double _stopLoss);
    
    virtual void OnNewBar(double sample) = 0;

    double GetProfits();

    bool IsActive() { return active; }

protected:
    double volume;

    double openPrice;
    int openBarIndex;

    double takeProfits;
    double stopLoss;

    // when the order gets closed
    double closePrice;
    int closeBarIndex;

    bool active;
};


class BuyOrder : public Order
{
public:
    BuyOrder(double volume, double price, double takeProfits, double stopLoss);

    virtual void OnNewBar(double sample);
};


class SellOrder : public Order
{
public:
    SellOrder(double volume, double price, double takeProfits, double stopLoss);

    virtual void OnNewBar(double sample);
};


enum OrderType
{
    tBUY,
    tSELL,
};

Order *CreateOrder(OrderType type, double lots, double price, double takeProfits, double stopLoss);

#endif