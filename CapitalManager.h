#ifndef __CapitalManager_H__
#define __CapitalManager_H__

#include <vector>
#include "Order.h"


class CapitalManager
{
public:
    CapitalManager();

    void SetFunds(double _balance);
    void SetLeverage(double _leverage);

    void AddOrder(Order *newOrder);

    void OnNewBar(double sample);

    bool NoOpenedOrders();

private:
    double balance;
    double equity;
    double leverage;

    std::vector<Order *> openedOrders;
};


#endif