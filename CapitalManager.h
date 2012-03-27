#ifndef __CapitalManager_H__
#define __CapitalManager_H__

#include <vector>
#include "Order.h"


class CapitalManager
{
public:
    CapitalManager();

    void SetFunds(double balance);
    void SetLeverage(double _leverage);

    void AddOrder(Order *newOrder);
    int GetNumOrders();
    void CloseAllOrders();
    Order *GetOrder(int index) { return orders[index]; }

    void OnNewBar(double sample, int timeIndex);

    bool NoOpenedOrders();

    void PrintReport();

private:
    double startBalance;
    double currentBalance;
    double equity;
    double leverage;

    unsigned int barCount;

    std::vector<Order *> orders;
};


#endif