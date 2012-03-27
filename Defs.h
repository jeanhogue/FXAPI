#ifndef __DEFS_H__
#define __DEFS_H__

enum Timeframe
{
    t1H,
};

static double CUR_POINT = 0.0001;

static double PipsToPrice(double pips)
{
    return pips * CUR_POINT;
}

#endif