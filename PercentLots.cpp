#include "PercentLots.h"
#include "Defs.h"


PercentLots::PercentLots(double _percent)
: LotsParameter("Lots", 0, 0, 0), percent(_percent)
{
}

double PercentLots::GetCurrentValue(double currentBalance, double stopLoss, double ask)
{ 
    // 1) Stop loss (in pips) * Value of one pip = n% * Balance
    // Problem: find the value of one pip so that 1) is true
    // 
    // If direct rate (EUR/USD, CHF/USD, etc.)
    //      2.1) Value in $ of one pip = 100000 * lots * points(= 0.0001)
    //      -> Lots = n% * balance / (SL * 100000 * 0.0001)
    //
    // If indirect rate (USD/CAD, USD/JPY, etc.)
    //      2.2) Value in $ of one pip = 100000 * lots * points(= 0.0001 or 0.01) / ask
    //      -> Lots = n% * balance * ask / (SL * 100000 * points)

    if (DIRECT_RATE)
        return currentBalance * percent / (stopLoss * 100000 * CUR_POINT);
    return currentBalance * percent * ask / (stopLoss * 100000 * CUR_POINT);
}
