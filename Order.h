#ifndef __Order_H__
#define __Order_H__


class Order
{
public:
    Order(double _volume, double price, double _takeProfits, double _stopLoss);
    
    virtual void OnNewBar(double sample) = 0;

    virtual double GetProfits() = 0;

    bool IsActive() { return active; }
    void CloseOrder() { active = false; }

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
    virtual double GetProfits();
};


class SellOrder : public Order
{
public:
    SellOrder(double volume, double price, double takeProfits, double stopLoss);

    virtual void OnNewBar(double sample);
    virtual double GetProfits();
};


enum OrderType
{
    tBUY,
    tSELL,
};

Order *CreateOrder(OrderType type, double lots, double price, double takeProfits, double stopLoss);

#endif