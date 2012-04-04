#ifndef __TradingParameter_H__
#define __TradingParameter_H__

#include <vector>
#include <string>
#include <cassert>


class TradingParameter
{
    friend class Optimizable;
public:
    TradingParameter(std::string _name, double _startValue, double _endValue, double _step);
    
    virtual double GetCurrentValue() { return currentValue; }

    void SaveParam();
    void SetBestParam();
    void Print();

protected:
    std::string name; 
    double startValue;
    double endValue;
    double step;
    double currentValue;
    double bestValue;       // value that gives best return
};


class LotsParameter : public TradingParameter
{
public:
    LotsParameter(std::string name, double startValue, double endValue, double step);

    virtual double GetCurrentValue(double currentBalance, double stopLoss, double ask) { return currentValue; }
};


class Optimizable
{
public:
    Optimizable();
    ~Optimizable();

    TradingParameter *AddTradingParameter(std::string name, double startValue, double endValue, double step);
    LotsParameter *AddLotsParameter(std::string name, double startValue, double endValue, double step);

    void SaveParameters();
    void SetBestParams();
    void PrintParameters();

    bool HasMoreParamsToTry();
    void UpdateParameters();

private:
    std::vector<TradingParameter *> parameters;
    int runCount;
};

#endif