#ifndef __DEFS_H__
#define __DEFS_H__

enum Timeframe
{
    t1H,
    t1D,
};

static double CUR_POINT = 0.01;
static double DIRECT_RATE = false;

static double PipsToPrice(double pips)
{
    return pips * CUR_POINT;
}

static double PriceToPips(double price)
{
    return price / CUR_POINT;
}

#endif