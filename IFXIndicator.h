#ifndef __IFXIndicator_H__
#define __IFXIndicator_H__

#include <vector>
#include "IFXActor.h"
#include "Colors.h"


class IFXIndicator : public IFXActor
{
public:
    // return value of the indicator at current bar
    virtual double GetValue() = 0;
    virtual double GetSampleAtIndex(int n);

    virtual void Render(int index, int numBarsToDraw, double minValue, double maxValue);

    virtual double GetMinValueInRange(int start, int end);
    virtual double GetMaxValueInRange(int start, int end);

    void SetColor(int r, int g, int b);
    Color &GetColor() { return color; }
    virtual bool IsIndicator() { return true; }

protected:
    std::vector<double> values;

    Color color;
};


#endif