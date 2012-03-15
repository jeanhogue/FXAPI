#include <Windows.h>
#include "glut.h"
#include <cmath>
#include "Renderer.h"
#include "RenderingUtils.h"


Renderer::Renderer(Simulator *_simulator)
: simulator(_simulator), offsetFromLatestBar(0), numBarsToDraw(30)
{
    CalculateMinMaxValues();
}

void Renderer::Render()
{
    RenderScales();
    RenderData();
    RenderActors();
}

void Renderer::Keypressed(unsigned char key)
{
    if (key == 39)      // right arrow
    {
        simulator->RunOneBar();
    }
}

void Renderer::RenderScales()
{
    
}

void Renderer::RenderData()
{
    glColor3f(1, 1, 1);
    DrawRectangleBorder(0.1f, 0.1f, 0.9f, 0.9f);
}

void Renderer::RenderActors()
{
    std::vector<IFXActor *> actors = simulator->GetActors();
    for (unsigned int i = 0; i < actors.size(); ++ i)
    {
        if (actors[i]->IsIndicator())
        {

        }
    }
}

void Renderer::CalculateMinMaxValues()
{
    minValue = HUGE_VAL;
    maxValue = -HUGE_VAL;

    std::vector<IFXActor *> actors = simulator->GetActors();
    for (unsigned int i = 0; i < actors.size(); ++ i)
    {
        if (actors[i]->IsIndicator())
        {
            double thisMin = actors[i]->GetMinValueInLastNBars(numBarsToDraw);
            double thisMax = actors[i]->GetMaxValueInLastNBars(numBarsToDraw);

            if (thisMin < minValue)
                minValue = thisMin;
            if (thisMax > maxValue)
                thisMax = maxValue;
        }
    }
}