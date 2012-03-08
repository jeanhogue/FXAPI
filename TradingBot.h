#ifndef __TradingBot_H__
#define __TradingBot_H__

#include "IFXActor.h"


class TradingBot : public IFXActor
{
public:
    void Init();
    void OnNewBar();
};

#endif