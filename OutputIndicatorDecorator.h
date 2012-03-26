#ifndef __OUTPUTINDICATORDECORATOR_H__
#define __OUTPUTINDICATORDECORATOR_H__

#include <string>
#include <fstream>
#include "IFXIndicator.h"


class OutputIndicatorDecorator : public IFXIndicator
{
public:
    OutputIndicatorDecorator(IFXIndicator *_decoree, const std::string &outFilename);
    ~OutputIndicatorDecorator();

    virtual void Init() { decoree->Init(); }
    virtual void OnNewBar(double sample, int timeIndex);

    virtual double GetValue() { return decoree->GetValue(); }

private:
    IFXIndicator *decoree;
    std::ofstream out;
};


#endif