#include <iostream>
#include <sstream>
#include "TradingParameter.h"


TradingParameter::TradingParameter(std::string _name, double _startValue, double _endValue, double _step)
: name(_name), startValue(_startValue), endValue(_endValue), step(_step), currentValue(_startValue), bestValue(startValue)
{
}

void TradingParameter::SaveParam()
{
    bestValue = currentValue;
}

void TradingParameter::SetBestParam()
{
    currentValue = bestValue;
}

void TradingParameter::Print()
{
    std::cout << name << " = " << currentValue << " ";
}


Optimizable::Optimizable()
: runCount(1)
{
}

Optimizable::~Optimizable()
{
    for (unsigned int i = 0; i < parameters.size(); ++ i)
        delete parameters[i];
}

TradingParameter *Optimizable::AddTradingParameter(std::string name, double startValue, double endValue, double step)
{
    TradingParameter *param = new TradingParameter(name, startValue, endValue, step);
    parameters.push_back(param);
    return param;
}

void Optimizable::SaveParameters()
{
    for (unsigned int i = 0; i < parameters.size(); ++ i)
        parameters[i]->SaveParam();
}

void Optimizable::SetBestParams()
{
    for (unsigned int i = 0; i < parameters.size(); ++ i)
        parameters[i]->SetBestParam();
}

void Optimizable::PrintParameters()
{
    std::cout << "#" << runCount << ": ";
    for (unsigned int i = 0; i < parameters.size(); ++ i)
        parameters[i]->Print();
    std::cout << std::endl;
}

bool Optimizable::HasMoreParamsToTry()
{
    TradingParameter *lastParam = parameters[parameters.size() - 1];
    return lastParam->GetCurrentValue() < lastParam->endValue;
}

void Optimizable::UpdateParameters()
{
    int index = 0;
    TradingParameter *param = parameters[index];

    while (1)
    {
        param->currentValue += param->step;
        // most common case, we just increment the parameter value with the step
        if (param->currentValue < param->endValue)
            break;

        // no more parameters to use
        if (index == parameters.size() - 1)
            break;

        // if parameter n when across the end value, we reset it to start value and increment the next parameter
        param->currentValue = param->startValue;
        param = parameters[++ index];
    }

    runCount ++;
}
