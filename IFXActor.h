#ifndef __IFXActor_H__
#define __IFXActor_H__


class IFXActor 
{
public:
    virtual void Init() = 0;
    virtual void Cleanup() {}
    virtual void OnNewBar(double sample, int timeIndex) = 0;

    virtual void Render(int index, int numBarsToDraw, double minValue, double maxValue) = 0;

    virtual double GetMinValueInRange(int start, int end) { return 0; }
    virtual double GetMaxValueInRange(int start, int end) { return 0; }

    virtual bool IsIndicator() { return false; }
    virtual bool IsTrader() { return false; }
};

#endif