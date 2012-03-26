#ifndef __Object_H__
#define __Object_H__

#include <string>


class Object
{
public:
    Object(int _timeIndex, double _price);

    virtual void Render(int latestBarIndex, int numBarsToDraw, double minValue, double maxValue) = 0;

    bool IsInScreen(int latestBarIndex, int numBarsToDraw);

protected:
    int timeIndex;
    double price;
};


class TextObj : public Object
{
public:
    TextObj(std::string _str, int timeIndex, double price);

    virtual void Render(int latestBarIndex, int numBarsToDraw, double minValue, double maxValue);

private:
    std::string str;
};


class OrderBar : public Object
{
public:
    OrderBar(int timeIndex, double price, double _takeProfit, double _stopLoss);

    virtual void Render(int latestBarIndex, int numBarsToDraw, double minValue, double maxValue);

private:
    double takeProfit;
    double stopLoss;
};

#endif