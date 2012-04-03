#ifndef __DEFS_H__
#define __DEFS_H__

enum Timeframe
{
    t1H,
    t1D,
};

static double CUR_POINT = 0.01;

static double PipsToPrice(double pips)
{
    return pips * CUR_POINT;
}

#endif