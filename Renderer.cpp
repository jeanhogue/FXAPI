#include <Windows.h>
#include "glut.h"
#include <cmath>
#include <sstream>
#include <string>
#include "Simulator.h"
#include "Renderer.h"
#include "RenderingUtils.h"
#include "IFXIndicator.h"
#include "TradingBot.h"


Renderer::Renderer(Simulator *_simulator)
: simulator(_simulator), offsetFromLatestBar(0), numBarsToDraw(30)
{
    reader = simulator->GetDataReader();
    CalculateMinMaxValues();
}

void Renderer::Render()
{
    RenderScales();
    RenderData();
    RenderActors();
}

void Renderer::KeyPressed(unsigned char key)
{
    if (key == 'o')      // right arrow
    {
        simulator->GoForwardNBars(5);
        CalculateMinMaxValues();
    }
    else if (key == 'a')     // left arrow
    {
        simulator->GoBackNBars(5);
        CalculateMinMaxValues();
    }
    else if (key == '+' || key == '=')
    {
        if (numBarsToDraw < 1000)
        {
            numBarsToDraw += 5;
            CalculateMinMaxValues();
        }
    }
    else if (key == '-')
    {
        if (numBarsToDraw > 5)
        {
            numBarsToDraw -= 5;
            CalculateMinMaxValues();
        }
    }
    glutPostRedisplay();
}

void Renderer::SetDimensions(int _width, int _height)
{
    width = _width;
    height = _height;
}

float Renderer::PixelsToWorldX(float x)
{
    return x / width;
}

float Renderer::PixelsToWorldY(float y)
{
    return y / height;
}

void Renderer::RenderScales()
{
    RenderScalesX();
    RenderScalesY();
}

double GetStep(double minValue, double maxValue)
{
    if (abs(maxValue - minValue) < 1e-10)
        return 1;

    // slide until we get only one significant digit
    double tmpMin = minValue;
    double tmpMax = maxValue;
    int slides = 0;
    if (std::min(abs(minValue), abs(maxValue)) >= 1)
    {
        int i = 0;
        while (abs(tmpMin) >= 10 && abs(tmpMax) >= 10 && i ++ < 10000)
        {
            tmpMin /= 10;
            tmpMax /= 10;
            slides ++;
        }

        i = 0;
        while ((int)tmpMax - (int)tmpMin <= 1 && i ++ < 10000)
        {
            tmpMax *= 10;
            tmpMin *= 10;
            slides --;
        }

        tmpMax = (double)(int)tmpMax;
        tmpMin = (double)(int)tmpMin;

        int R = (int)(tmpMin - ((int)tmpMin % 5) + 5);

        if (R > tmpMax)
        {
            R = (int)((tmpMin + tmpMax) / 2);
            if (R % 2 == 1)
                R ++;
        }

        return R * pow(10.f, slides);
    }
    else
    {
        int i = 0;
        while (abs(tmpMin) < 1 && abs(tmpMax) < 1 && i ++ < 10000)
        {
            tmpMin *= 10;
            tmpMax *= 10;
            slides ++;
        }

        i = 0;
        while ((int)tmpMax - (int)tmpMin <= 1 && i ++ < 10000)
        {
            tmpMax *= 10;
            tmpMin *= 10;
            slides ++;
        }

        tmpMax = (double)(int)tmpMax;
        tmpMin = (double)(int)tmpMin;

        int R = (int)(tmpMin - ((int)tmpMin % 5) + 5);

        if (R > tmpMax)
        {
            R = (int)((tmpMin + tmpMax) / 2);
            if (R % 2 == 1)
                R ++;
        }

        return R * pow(10.f, -slides);
    }
}

void Renderer::RenderScalesX()
{

}

void Renderer::RenderScalesY()
{
    // check to avoid infinite loop
    if (maxValue - minValue > 1e30)
        return;

    static const int gridMinPixelCount = 40;
    static const int gridMaxPixelCount = 70;

    double referencePoint = 0;
    if (minValue < 0 && maxValue > 0)
    {
        // put the reference point where the 0 of the data is
        referencePoint = 0;
    }
    else
    {
        // put the reference point at a easily human readable place
        referencePoint = GetStep(minValue, maxValue);
        if (referencePoint < minValue)
            referencePoint = minValue;
    }

    float ratioMinPixels = gridMinPixelCount / (height - 2 * borderH);
    float ratioMaxPixels = gridMaxPixelCount / (height - 2 * borderH);
    int count = 0;
    while (ratioMaxPixels > 0.85f && count ++ < 10)
    {
        // to solve the problem where the max pixel threshold is above the window dimension
        // and no grid lines are shown,
        // decrease the min/max thresholds until at least one grid line will fit
        ratioMinPixels = gridMinPixelCount / (count + 1) / (height - 2 * borderH);
        ratioMaxPixels = gridMaxPixelCount / (count + 1) / (height - 2 * borderH);
    }

    double step = abs(GetStep(ratioMinPixels * (maxValue - minValue), ratioMaxPixels * (maxValue - minValue)));

    // infinite loop check
    if (step <= 1e-10)
        return;

    // draw the X axis scale lines
    double startPoint = referencePoint;
    int negCount = 0;
    while (startPoint > minValue)
    {
        startPoint -= step;
        negCount ++;
    }
    negCount --;
    
    glViewport(offsetX + borderW, offsetY + borderH, width - 2 * borderW, height - 2 * borderH);
    
    for (double i = startPoint + step, count = 0; i < maxValue; i += step, count ++)
    {
        glColor3f(0.65f, 0.65f, 0.65f);
        DrawLineStipple(0, (i - minValue) / (maxValue - minValue),
                        1, (i - minValue) / (maxValue - minValue));
    }

    glViewport(offsetX, offsetY, width, height);

    // draw the y axis scale numbers
    glColor3f(0.2f, 0.2f, 0.2f);
    for (double i = startPoint + step, count = 0; i < maxValue; i += step, count ++)
    {
        float y = PixelsToWorldY(borderH + (i - minValue) / (maxValue - minValue) * (height - 2 * borderH), false);

        std::stringstream ss;
        ss << i;

        RenderText(*dc, PixelsToWorldX(borderW * 4 / 5, false), CheckFlipY(y), wxString(ss.str().c_str(), wxConvUTF8), eFtSmall, eCentered, 90.0);
    }
}

void Renderer::RenderData()
{
    float POINT_WIDTH = PixelsToWorldX(5);
    float POINT_HEIGHT = PixelsToWorldY(5);

    glColor3f(0, 1, 0);
    for (int i = 0; i < numBarsToDraw; ++ i)
    {
        double sample = reader->GetSampleNBarsAgo(i + simulator->GetCurrentIndex());
        float x = 1 - i / (float)numBarsToDraw;
        float y = (sample - minValue) / (maxValue - minValue);
        
        DrawRectangle(x - POINT_WIDTH, y - POINT_HEIGHT, x + POINT_WIDTH, y + POINT_HEIGHT);
    }
}

void Renderer::RenderActors()
{
    std::vector<IFXActor *> actors = simulator->GetActors();
    for (unsigned int i = 0; i < actors.size(); ++ i)
    {
        if (actors[i]->IsIndicator())
            RenderActor((IFXIndicator *)actors[i]);
        else if (actors[i]->IsTrader())
            RenderTrader((TradingBot *)actors[i]);
    }
}

void Renderer::RenderTrader(TradingBot *trader)
{
    std::vector<IFXIndicator *> indicators = trader->GetIndicators();

    for (unsigned int i = 0; i < indicators.size(); ++ i)
    {
        RenderActor(indicators[i]);
    }
}

void Renderer::RenderActor(IFXIndicator *actor)
{
    float POINT_WIDTH = PixelsToWorldX(5);
    float POINT_HEIGHT = PixelsToWorldY(5);

    float lastPointX = -1; 
    float lastPointY = -1;

    glColor3f(1, 0, 0);
    for (int i = 0; i < numBarsToDraw; ++ i)
    {
        double sample = actor->GetSampleNBarsAgo(i + simulator->GetCurrentIndex());
        float x = 1 - i / (float)numBarsToDraw;
        float y = (sample - minValue) / (maxValue - minValue);

        if (i == 0)
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
    }
}

void Renderer::CalculateMinMaxValues()
{
    int index = simulator->GetCurrentIndex();
    minValue = reader->GetMinValueInRange(index, index + numBarsToDraw);
    maxValue = reader->GetMaxValueInRange(index, index + numBarsToDraw);

    std::vector<IFXActor *> actors = simulator->GetActors();
    for (unsigned int i = 0; i < actors.size(); ++ i)
    {
        if (actors[i]->IsIndicator())
        {
            double thisMin = actors[i]->GetMinValueInRange(index, index + numBarsToDraw);
            double thisMax = actors[i]->GetMaxValueInRange(index, index + numBarsToDraw);

            if (thisMin < minValue)
                minValue = thisMin;
            if (thisMax > maxValue)
                thisMax = maxValue;
        }
    }

    double diff = maxValue - minValue;
    minValue -= diff * 0.1f;
    maxValue += diff * 0.1f;
}