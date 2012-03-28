#include "IFXIndicator.h"
#include <cmath>


double IFXIndicator::GetSampleAtIndex(int n)
{
    if (n >= (int)values.size())
        return 0;
    return values[n];
}

double IFXIndicator::GetMinValueInRange(int start, int end)
{
    double minValue = HUGE_VAL;

    int count = 0;
    for (int i = (int)values.size() - 1 - start; i >= 0 && count < end - start; -- i, ++ count)
    {
        if (values[i] < minValue)
            minValue = values[i];
    }

    return minValue;
}

double IFXIndicator::GetMaxValueInRange(int start, int end)
{
    double maxValue = HUGE_VAL;

    int count = 0;
    for (int i = (int)values.size() - 1 - start; i >= 0 && count < end - start; -- i, ++ count)
    {
        if (values[i] > maxValue)
            maxValue = values[i];
    }

    return maxValue;
}

void IFXIndicator::SetColor(int r, int g, int b)
{
    color.SetColor(r, g, b);
}