#ifndef __RENDERER_H__
#define __RENDERER_H__


class Simulator;
class ObjectManager;
class DataReader;
class TradingBot;

class IFXIndicator;

class Renderer
{
public:
    Renderer(Simulator *_simulator, ObjectManager *_objectManager);

    void RenderBorders(float normBorderX, float normBorderY);
    void Render();

    void KeyPressed(unsigned char key);
    void SetDimensions(int _width, int _height);

private:
    float PixelsToWorldX(float x);
    float PixelsToWorldY(float y);

    void RenderScalesX(float normBorderX, float normBorderY);
    void RenderScalesY(float normBorderX, float normBorderY);
    void RenderData();
    void RenderActors();
    void RenderTrader(TradingBot *trader);
    void RenderActor(IFXIndicator *actor);
    void RenderObjects();

    void CalculateMinMaxValues();

    Simulator *simulator;
    ObjectManager *objectManager;
    DataReader *reader;

    int offsetFromLatestBar;
    int numBarsToDraw;
    double minValue, maxValue;

    int width;
    int height;
};


void StartRendering(int argc, char **argv, Renderer *_renderer);

#endif