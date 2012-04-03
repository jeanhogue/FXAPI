#include <iostream>
#include "CapitalManager.h"


CapitalManager::CapitalManager()
: equity(0), leverage(100), barCount(0)
{
}

void CapitalManager::Cleanup()
{
    for (unsigned int i = 0; i < orders.size(); ++ i)
        delete orders[i];
    orders.clear();
}

double CapitalManager::GetFunds() 
{ 
    return currentBalance; 
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

    if (orders.size() == 154)
    {
        int bla = 2;
    }
}

int CapitalManager::GetNumPositiveOrders()
{
    int count = 0;
    for (size_t i = 0; i < orders.size(); ++ i)
    {
        if (orders[i]->IsGain())
            count ++;
    }
    return count;
}

int CapitalManager::GetNumNegativeOrders()
{
    int count = 0;
    for (size_t i = 0; i < orders.size(); ++ i)
    {
        if (!orders[i]->IsGain())
            count ++;
    }
    return count;
}

int CapitalManager::GetNumOrders()
{
    return (int)orders.size();
}

void CapitalManager::CloseAllOrders(double sample)
{
    for (size_t i = 0; i < orders.size(); ++ i)
    {
        if (orders[i]->IsActive())
        {
            orders[i]->CloseOrder(sample);
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
    std::cout << "Orders (Gain, Loss, Total) = " << GetNumPositiveOrders() << ", " << GetNumNegativeOrders() << ", " << GetNumOrders() << std::endl;
}