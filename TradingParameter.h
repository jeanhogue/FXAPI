#ifndef __TradingParameter_H__
#define __TradingParameter_H__

#include <vector>
#include <string>


class TradingParameter
{
    friend class Optimizable;
public:
    TradingParameter(std::string _name, double _startValue, double _endValue, double _step);

    double GetCurrentValue() { return currentValue; }

    void Print();

private:
    std::string name; 
    double startValue;
    double endValue;
    double step;
    double currentValue;
};


class Optimizable
{
public:
    Optimizable();
    ~Optimizable();

    TradingParameter *AddTradingParameter(std::string name, double startValue, double endValue, double step);

    void PrintParameters();

    bool HasMoreParamsToTry();
    void UpdateParameters();

private:
    std::vector<TradingParameter *> parameters;
    int runCount;
};

#endif