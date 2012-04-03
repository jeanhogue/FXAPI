#include <cmath>
#include "BollingerBands.h"
#include "MovingAverage.h"
#include "RenderingUtils.h"


BollingerBands::BollingerBands(int _period, float _D)
: period(_period), D(_D), buffer(0)
{
    movingAverage = CreateMA(tSMA, period);

    SetColor(255, 127, 39);
}

BollingerBands::~BollingerBands()
{
    if (buffer)
        delete [] buffer;
    delete movingAverage;
}


void BollingerBands::Init()
{
    buffer = new double[period];
    memset(buffer, 0, sizeof(double) * period);

    movingAverage->Init();
    movingAverage->SetColor(200, 100, 15);
}

void BollingerBands::OnNewBar(double sample, int timeIndex)
{
    movingAverage->OnNewBar(sample, timeIndex);

    // move all samples in the buffer one place left and 
    // store the new sample at the end 
    for (int i = 1; i < period; ++ i)
        buffer[i - 1] = buffer[i];
    buffer[period - 1] = sample;

    values.push_back(movingAverage->GetCurrentValue());

    // Upper BB = MA + D * sqrt(sum(yi - MA)^2 / n)
    // Lower BB = MA - D * sqrt(sum(yi - MA)^2 / n)

    double sum = 0;
    for (int i = 0; i < period && timeIndex - period + i >= 0; ++ i)
        sum += pow(buffer[i] - movingAverage->GetSampleAtIndex(timeIndex - period + i), 2);

    // Only store the right term in the BB vector
    // We'll do MA +- only when it's time to render
    BB.push_back(D * sqrt(sum / period));
}

void BollingerBands::Render(int index, int numBarsToDraw, double minValue, double maxValue)
{
    movingAverage->Render(index, numBarsToDraw, minValue, maxValue);

    float lastPointX = -1; 
    float lastPointY1 = -1;
    float lastPointY2 = -1;

    float halfBoxWidth = PixelsToWorldX(2);
    float halfBoxHeight = PixelsToWorldY(2);

    color.SetOGLColor();
    for (int i = 0; i < numBarsToDraw; ++ i)
    {
        if (i > index)
            break;

        if (index - i >= (int)values.size())
            continue;

        double upperBB = movingAverage->GetSampleAtIndex(index - i) + BB[index - i];
        double lowerBB = movingAverage->GetSampleAtIndex(index - i) - BB[index - i];
        float x = 1 - i / (float)numBarsToDraw;
        float y1 = (upperBB - minValue) / (maxValue - minValue);
        float y2 = (lowerBB - minValue) / (maxValue - minValue);

        if (lastPointX < 0)
        {
            lastPointX = x;
            lastPointY1 = y1;
            lastPointY2 = y2;
        }
        else
        {
            DrawLine(x, y1, lastPointX, lastPointY1);
            DrawLine(x, y2, lastPointX, lastPointY2);

            lastPointX = x;
            lastPointY1 = y1;
            lastPointY2 = y2;
        }

        DrawRectangle(x - halfBoxWidth, y1 - halfBoxHeight, x + halfBoxWidth, y1 + halfBoxHeight);
        DrawRectangle(x - halfBoxWidth, y2 - halfBoxHeight, x + halfBoxWidth, y2 + halfBoxHeight);
    }
}