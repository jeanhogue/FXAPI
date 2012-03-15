#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Simulator.h"


class Renderer
{
public:
    Renderer(Simulator *_simulator);

    void Render();

    void Keypressed(unsigned char key);

private:
    void RenderScales();
    void RenderData();
    void RenderActors();

    void CalculateMinMaxValues();

    Simulator *simulator;

    int offsetFromLatestBar;
    int numBarsToDraw;
    double minValue, maxValue;
};


void StartRendering(int argc, char **argv, Renderer *_renderer);

#endif