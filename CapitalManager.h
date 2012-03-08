#ifndef __CapitalManager_H__
#define __CapitalManager_H__

#include <vector>
#include "Order.h"


class CapitalManager
{
public:

private:
    std::vector<Order *> openedOrders;
};


#endif