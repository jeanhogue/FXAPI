#include "MATrader.h"
#include "MovingAverage.h"


MATrader::MATrader(CapitalManager *capitalManager, ObjectManager *objectManager)
: TradingBot(capitalManager, objectManager)
{
}

void MATrader::Init()
{
    slowMA = CreateMA(tEMA, 8);
    fastMA = CreateMA(tEMA, 5);
 
    slowMA->Init();
    fastMA->Init();

    indicators.push_back(slowMA);
    indicators.push_back(fastMA);

    state = 0;
    barCount = 0;
}

void MATrader::OnNewBar(double sample)
{
    slowMA->OnNewBar(sample);
    fastMA->OnNewBar(sample);
    barCount ++;

    int newState = GetState();

    if (barCount >= INIT_PERIOD)
    {
        if (newState != state)
        {
            // a crossover happened; generate a signal
            if (newState == 1)
                Buy(sample);
            else
                Sell(sample);
        }
    }
    
    state = newState;
}

int MATrader::GetState()
{
    if (fastMA->GetValue() >= slowMA->GetValue())
        return 1;
    return -1;
}