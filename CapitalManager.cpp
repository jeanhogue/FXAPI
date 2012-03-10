#include "CapitalManager.h"


CapitalManager::CapitalManager()
: equity(0), balance(0), leverage(100)
{
}

void CapitalManager::SetFunds(double _balance)
{
    balance = _balance;
}

void CapitalManager::SetLeverage(double _leverage)
{
    leverage = _leverage;
}

void CapitalManager::AddOrder(Order *newOrder)
{
    openedOrders.push_back(newOrder);
}

void CapitalManager::OnNewBar(double sample)
{
    for (size_t i = 0; i < openedOrders.size(); ++ i)
    {
        if (openedOrders[i]->IsActive())
        {
            openedOrders[i]->OnNewBar(sample);

            // if the order was closed on this bar, adjust the balance according to the profits/losses
            balance += openedOrders[i]->GetProfits();
        }
    }
}

bool CapitalManager::NoOpenedOrders()
{
    for (size_t i = 0; i < openedOrders.size(); ++ i)
    {
        if (openedOrders[i]->IsActive())
            return false;
    }
    return true;
}