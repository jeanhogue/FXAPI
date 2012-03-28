#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>

class Simulator;
class ObjectManager;
class DataReader;
class TradingBot;

class IFXActor;
class IFXIndicator;

class Renderer
{
public:
    Renderer(Simulator *_simulator, ObjectManager *_objectManager);

    void RenderBorders(float normBorderX, float normBorderY);
    void Render();

    void KeyPressed(unsigned char key);
    void OnMotion(int x, int y);
    void SetDimensions(int _width, int _height);

private:
    void RenderCursor(float normBorderY);
    void RenderScalesX(float normBorderX, float normBorderY);
    void RenderScalesY(float normBorderX, float normBorderY);
    void RenderData();

    void CalculateMinMaxValues();

    Simulator *simulator;
    ObjectManager *objectManager;
    DataReader *reader;

    int offsetFromLatestBar;
    int numBarsToDraw;
    double minValue, maxValue;

    bool drawCursor;
    float mouseX;
    float mouseY;
};


void StartRendering(int argc, char **argv, Renderer *_renderer);

#endif