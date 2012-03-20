#ifndef __IFXIndicator_H__
#define __IFXIndicator_H__

#include <vector>
#include "IFXActor.h"


class IFXIndicator : public IFXActor
{
public:
    // return value of the indicator at current bar
    virtual double GetValue() = 0;
    virtual double GetSampleNBarsAgo(int n);

    virtual double GetMinValueInRange(int start, int end);
    virtual double GetMaxValueInRange(int start, int end);

    virtual bool IsIndicator() { return true; }

protected:
    std::vector<double> values;
};


#endif