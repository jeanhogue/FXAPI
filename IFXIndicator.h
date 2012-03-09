#ifndef __IFXIndicator_H__
#define __IFXIndicator_H__

#include "IFXActor.h"


class IFXIndicator : public IFXActor
{
public:
    // return value of the indicator at current bar
    virtual double GetValue() = 0;
};


#endif