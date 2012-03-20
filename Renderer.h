#ifndef __RENDERER_H__
#define __RENDERER_H__


class Simulator;
class DataReader;
class TradingBot;

class IFXIndicator;

class Renderer
{
public:
    Renderer(Simulator *_simulator);

    void Render();

    void KeyPressed(unsigned char key);
    void SetDimensions(int _width, int _height);

private:
    float PixelsToWorldX(float x);
    float PixelsToWorldY(float y);

    void RenderScales();
    void RenderData();
    void RenderActors();
    void RenderTrader(TradingBot *trader);
    void RenderActor(IFXIndicator *actor);

    void CalculateMinMaxValues();

    Simulator *simulator;
    DataReader *reader;

    int offsetFromLatestBar;
    int numBarsToDraw;
    double minValue, maxValue;

    int width;
    int height;
};


void StartRendering(int argc, char **argv, Renderer *_renderer);

#endif