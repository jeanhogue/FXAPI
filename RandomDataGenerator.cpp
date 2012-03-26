#include "RandomDataGenerator.h"
#include <time.h>


RandomDataGenerator::RandomDataGenerator(double _startPrice, int _numBars)
: DataReader(t1H), startPrice(_startPrice), range(_startPrice * 0.02), numBars(_numBars), momentum(0)
{
    //srand(time(NULL));
}

double RandomDataGenerator::GetNextTick()
{
    double a = (float)rand() / RAND_MAX;
    momentum += a * range - range / 2;

    double sample;
    if (data.empty())
        sample = startPrice + momentum;
    else
        sample = data[data.size() - 1] + momentum;

    data.push_back(sample);

    return sample;
}

bool RandomDataGenerator::EndOfData()
{
    return (int)data.size() >= numBars;
}