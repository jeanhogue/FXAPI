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
#include "ObjectManager.h"
#include "Object.h"


Renderer::Renderer(Simulator *_simulator, ObjectManager *_objectManager)
: simulator(_simulator), objectManager(_objectManager), offsetFromLatestBar(0), numBarsToDraw(30)
{
    reader = simulator->GetDataReader();
    CalculateMinMaxValues();
}

void Renderer::RenderBorders(float normBorderX, float normBorderY)
{
    glColor3f(0.8f, 0.8f, 0.8f);
    RenderScalesX(normBorderX, normBorderY);
    RenderScalesY(normBorderX, normBorderY);

    glColor3f(1, 1, 1);
    DrawRectangleBorder(normBorderX, normBorderY, 1 - normBorderX, 1 - normBorderY);
}

void Renderer::Render()
{
    RenderData();
    RenderActors();
    RenderObjects();
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

void Renderer::RenderScalesX(float normBorderX, float normBorderY)
{
}

void Renderer::RenderScalesY(float normBorderX, float normBorderY)
{
    int numLinesToDraw = height / 75;

    float renderingAreaY = 1 - normBorderY * 2;

    glColor3f(1, 1, 1);
    for (int i = 1; i < numLinesToDraw + 1; ++ i)
    {
        float ratio = i / (float)(numLinesToDraw + 1);
        float y = normBorderY + (1 - 2 * normBorderY) * ratio;
        DrawLine(normBorderX, y, 1 - normBorderX, y);

        std::stringstream ss;
        ss << (maxValue - minValue) * ratio;
        Print(ss.str(), 0.94f, y);
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

void Renderer::RenderObjects()
{
    std::vector<Object *> objects = objectManager->GetObjects();

    for (unsigned int i = 0; i < objects.size(); ++ i)
        objects[i]->Render();
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