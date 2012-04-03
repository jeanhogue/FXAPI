#include <cmath>
#include "IFXIndicator.h"
#include "RenderingUtils.h"


double IFXIndicator::GetCurrentValue()
{
    if (values.empty())
        return -1;
    return values[values.size() - 1];
}

double IFXIndicator::GetSampleAtIndex(int n)
{
    if (n >= (int)values.size())
        return 0;
    return values[n];
}

void IFXIndicator::Render(int index, int numBarsToDraw, double minValue, double maxValue)
{
    float lastPointX = -1; 
    float lastPointY = -1;

    float halfBoxWidth = PixelsToWorldX(2);
    float halfBoxHeight = PixelsToWorldY(2);

    color.SetOGLColor();
    for (int i = 0; i < numBarsToDraw; ++ i)
    {
        if (i > index)
            break;

        if (index - i >= (int)values.size())
            continue;

        double sample = GetSampleAtIndex(index - i);
        float x = 1 - i / (float)numBarsToDraw;
        float y = (sample - minValue) / (maxValue - minValue);

        if (lastPointX < 0)
        {
            lastPointX = x;
            lastPointY = y;
        }
        else
        {
            DrawLine(x, y, lastPointX, lastPointY);

            lastPointX = x;
            lastPointY = y;
        }

        DrawRectangle(x - halfBoxWidth, y - halfBoxHeight, x + halfBoxWidth, y + halfBoxHeight);
    }
}

double IFXIndicator::GetMinValueInRange(int start, int end)
{
    double minValue = HUGE_VAL;

    if (start < 0)
        start = 0;

    for (int i = start + 1; i < end && i < (int)values.size(); ++ i)
    {
        if (values[i] < minValue)
            minValue = values[i];
    }

    return minValue;
}

double IFXIndicator::GetMaxValueInRange(int start, int end)
{
    double maxValue = HUGE_VAL;

    if (start < 0)
        start = 0;

    for (int i = start + 1; i < end && i < (int)values.size(); ++ i)
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