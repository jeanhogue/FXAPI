#ifndef __CapitalManager_H__
#define __CapitalManager_H__

#include <vector>
#include "Order.h"


class CapitalManager
{
public:
    CapitalManager();

    void Cleanup();

    double GetFunds();
    void SetFunds(double balance);
    void SetLeverage(double _leverage);

    void AddOrder(Order *newOrder);
    
    int GetNumPositiveOrders();
    int GetNumNegativeOrders();
    int GetNumOrders();
    
    void CloseAllOrders(double sample);
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