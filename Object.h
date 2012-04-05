#ifndef __Object_H__
#define __Object_H__

#include <string>
#include "Colors.h"


class Object
{
public:
    Object(int _timeIndex, double _price);

    virtual void Render(int latestBarIndex, int numBarsToDraw, double minValue, double maxValue) = 0;

    void SetColor(int r, int g, int b) { color.SetColor(r, g, b); }

    bool IsInScreen(int latestBarIndex, int numBarsToDraw);

protected:
    int timeIndex;
    double price;

    Color color;
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

    void OrderClosed(int timeIndex, double price);

private:
    double takeProfit;
    double stopLoss;

    int closeTimeIndex;
    double closePrice;
};

#endif