#include <iostream>
#include "CapitalManager.h"


CapitalManager::CapitalManager()
: equity(0), leverage(100), barCount(0)
{
}

void CapitalManager::SetFunds(double balance)
{
    startBalance = balance;
    currentBalance = balance;
}

void CapitalManager::SetLeverage(double _leverage)
{
    leverage = _leverage;
}

void CapitalManager::AddOrder(Order *newOrder)
{
    orders.push_back(newOrder);
}

int CapitalManager::GetNumOrders()
{
    return orders.size();
}

void CapitalManager::CloseAllOrders()
{
    for (size_t i = 0; i < orders.size(); ++ i)
    {
        if (orders[i]->IsActive())
        {
            orders[i]->CloseOrder();
            currentBalance += orders[i]->GetProfits();
        }
    }
}

void CapitalManager::OnNewBar(double sample, int timeIndex)
{
    for (size_t i = 0; i < orders.size(); ++ i)
    {
        if (orders[i]->IsActive())
        {
            orders[i]->OnNewBar(sample);

            if (!orders[i]->IsActive())
            {
                // if the order was closed on this bar, adjust the balance according to the profits/losses
                currentBalance += orders[i]->GetProfits();
            }
        }
    }

    barCount ++;
}

bool CapitalManager::NoOpenedOrders()
{
    for (size_t i = 0; i < orders.size(); ++ i)
    {
        if (orders[i]->IsActive())
            return false;
    }
    return true;
}

void CapitalManager::PrintReport()
{
    std::cout << "Start balance = " << startBalance << ", End Balance = " << currentBalance << ", Profits = " << (currentBalance - startBalance) / startBalance  * 100 << "%" << std::endl;
    std::cout << "Number orders = " << orders.size() << std::endl;
    std::cout << "Number bars = " << barCount << std::endl;
}