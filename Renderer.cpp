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
: simulator(_simulator), objectManager(_objectManager), numBarsToDraw(50)
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

    DrawLine(mouseX, 0, mouseX, 1);
    DrawLine(0, mouseY, 1, mouseY);

    // print the price value next to the cursor
    double diff = maxValue - minValue;
    double middle = (maxValue + minValue) / 2;
    double delta = diff * height / (height - 2 * normBorderY * height) / 2;
    double fullMaxValue = middle + delta;
    double fullMinValue = middle - delta;
    std::stringstream ss;
    ss << fullMinValue + mouseY * (fullMaxValue - fullMinValue);
    Print(ss.str(), mouseX + PixelsToWorldX(5), mouseY + PixelsToWorldY(5));
}

void Renderer::Render()
{
    RenderData();
    RenderActors(simulator->GetActors());
    RenderObjects();
}

void Renderer::KeyPressed(unsigned char key)
{
    if (key == 'o')
    {
        simulator->GoForwardNBars(5);
        CalculateMinMaxValues();
    }
    else if (key == 'a')
    {
        simulator->GoBackNBars(5);
        CalculateMinMaxValues();
    }
    else if (key == ';')
    {
        if (simulator->GoToPreviousOrder())
            simulator->GoForwardNBars(numBarsToDraw / 2);
        CalculateMinMaxValues();
    }
    else if (key == 'q')
    {
        if (simulator->GoToNextOrder())
            simulator->GoForwardNBars(numBarsToDraw / 2);
        CalculateMinMaxValues();
    }
    else if (key == '-')
    {
        if (numBarsToDraw < 1000)
        {
            numBarsToDraw += 5;
            CalculateMinMaxValues();
        }
    }
    else if (key == '+' || key == '=')
    {
        if (numBarsToDraw > 5)
        {
            numBarsToDraw -= 5;
            CalculateMinMaxValues();
        }
    }
    glutPostRedisplay();
}

void Renderer::OnMotion(int x, int y)
{
    mouseX = (float)x / width;
    mouseY = 1 - (float)y / height;

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

    double diff = maxValue - minValue;

    glColor3f(1, 1, 1);
    for (int i = 1; i < numLinesToDraw + 1; ++ i)
    {
        float ratio = i / (float)(numLinesToDraw + 1);
        float y = normBorderY + (1 - 2 * normBorderY) * ratio;
        DrawLine(1 - normBorderX, y, 1 - normBorderX * 2 / 3, y);

        std::stringstream ss;
        ss << minValue + diff * ratio;
        Print(ss.str(), 0.94f, y);
    }
}

void Renderer::RenderData()
{
    float SPACE_BETWEEN_BARS = PixelsToWorldX(5);
    float POINT_WIDTH = PixelsToWorldX((float)width / numBarsToDraw) - SPACE_BETWEEN_BARS;
    float POINT_HEIGHT = PixelsToWorldY(5);

    int index = simulator->GetCurrentIndex();

    double diff = maxValue - minValue;

    glColor3f(0, 1, 0);
    for (int i = 0; i < numBarsToDraw; ++ i)
    {
        double sample = reader->GetSampleAtIndex(index - i);
        float x = 1 - i / (float)numBarsToDraw;
        float y = (sample - minValue) / diff;
        
        DrawRectangle(x - POINT_WIDTH / 2, y - POINT_HEIGHT, x + POINT_WIDTH / 2, y + POINT_HEIGHT);
    }
}

void Renderer::RenderActors(std::vector<IFXActor *> actors)
{
    for (unsigned int i = 0; i < actors.size(); ++ i)
    {
        if (actors[i]->IsIndicator())
            RenderActor((IFXIndicator *)actors[i]);
        else if (actors[i]->IsTrader())
            RenderActors(((TradingBot *)actors[i])->GetIndicators());
    }
}

void Renderer::RenderActor(IFXIndicator *actor)
{
    float lastPointX = -1; 
    float lastPointY = -1;

    int index = simulator->GetCurrentIndex();

    SetColor(actor->GetColor());
    for (int i = 0; i < numBarsToDraw; ++ i)
    {
        double sample = actor->GetSampleAtIndex(index - i);
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

    int index = simulator->GetCurrentIndex();

    for (unsigned int i = 0; i < objects.size(); ++ i)
    {
        if (objects[i]->IsInScreen(index, numBarsToDraw))
            objects[i]->Render(index, numBarsToDraw, minValue, maxValue);
    }
}

void Renderer::CalculateMinMaxValues()
{
    int index = simulator->GetCurrentIndex();
    minValue = reader->GetMinValueInRange(index - numBarsToDraw, index);
    maxValue = reader->GetMaxValueInRange(index - numBarsToDraw, index);

    std::vector<IFXActor *> actors = simulator->GetActors();
    for (unsigned int i = 0; i < actors.size(); ++ i)
    {
        if (!actors[i]->IsIndicator())
            continue;
        
        double thisMin = actors[i]->GetMinValueInRange(index - numBarsToDraw, index);
        double thisMax = actors[i]->GetMaxValueInRange(index - numBarsToDraw, index);

        if (thisMin < minValue)
            minValue = thisMin;
        if (thisMax > maxValue)
            thisMax = maxValue;
    }

    double diff = maxValue - minValue;
    minValue -= diff * 0.05;
    maxValue += diff * 0.05;
}