#include "MATrader.h"
#include "MovingAverage.h"


MATrader::MATrader(CapitalManager *capitalManager, ObjectManager *objectManager)
: TradingBot(capitalManager, objectManager)
{
}

void MATrader::Init()
{
    slowMA = CreateMA(tEMA, 13);
    fastMA = CreateMA(tEMA, 5);
 
    slowMA->Init();
    fastMA->Init();

    slowMA->SetColor(200, 20, 133);
    fastMA->SetColor(123, 104, 238);

    indicators.push_back(slowMA);
    indicators.push_back(fastMA);

    state = 0;
    barCount = 0;
}

void MATrader::OnNewBar(double sample, int timeIndex)
{
    slowMA->OnNewBar(sample, timeIndex);
    fastMA->OnNewBar(sample, timeIndex);
    barCount ++;

    int newState = GetState();

    if (barCount >= INIT_PERIOD)
    {
        if (newState != state)
        {
            // a crossover happened; generate a signal
            if (newState == 1)
                Buy(sample, timeIndex);
            else
                Sell(sample, timeIndex);
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