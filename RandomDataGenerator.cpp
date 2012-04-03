#include "RandomDataGenerator.h"
#include <ctime>
#include <cmath>


RandomDataGenerator::RandomDataGenerator(double _startPrice, int _numBars, int _seed)
: DataReader(t1H), startPrice(_startPrice), numBars(_numBars), seed(_seed)
{
}

void RandomDataGenerator::Init()
{
    srand(seed);
    lastSample = startPrice;     // start value
}

double RandomDataGenerator::GetNextTick()
{
    static const double T = 1.00;            // expiry time
    static const double sigma = 0.15;        // volatility
    static const double mu = .10;            // P measure drift
    static const double delt = T / numBars;  // timestep
    static const double drift = mu * delt;
    static const double sigma_sqrt_delt = sigma * sqrt(delt);

    double sample = lastSample + lastSample * (drift + sigma_sqrt_delt * (2 * (float)rand() / RAND_MAX - 1));
    lastSample = sample;
    
    data.push_back(sample);

    return sample;
}

bool RandomDataGenerator::EndOfData()
{
    return (int)data.size() >= numBars;
}