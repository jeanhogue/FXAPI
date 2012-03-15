#include "IFXIndicator.h"
#include <cmath>


double IFXIndicator::GetMinValueInLastNBars(int nBars)
{
    double minValue = HUGE_VAL;

    int count = 0;
    for (int i = (int)values.size() - 1; i >= 0 && count < nBars; -- i, ++ count)
    {
        if (values[i] < minValue)
            minValue = values[i];
    }

    return minValue;
}

double IFXIndicator::GetMaxValueInLastNBars(int nBars)
{
    double maxValue = HUGE_VAL;

    int count = 0;
    for (int i = (int)values.size() - 1; i >= 0 && count < nBars; -- i, ++ count)
    {
        if (values[i] > maxValue)
            maxValue = values[i];
    }

    return maxValue;
}