#include "RandomDataGenerator.h"
#include <ctime>
#include <cmath>


RandomDataGenerator::RandomDataGenerator(double _startPrice, int _numBars)
: DataReader(t1H), startPrice(_startPrice), range(_startPrice * 0.02), numBars(_numBars)
{
    //srand(time(NULL));
    lastSample = 1;     // start value
}

double RandomDataGenerator::GetNextTick()
{
    double T = 1.00;            // expiry time
    double sigma = 0.25;        // volatility
    double mu = .10;            // P measure drift
    double delt = T / numBars;  // timestep
    double drift = mu * delt;
    double sigma_sqrt_delt = sigma * sqrt(delt);

    double sample = lastSample + lastSample * (drift + sigma_sqrt_delt * (2 * (float)rand() / RAND_MAX - 1));
    lastSample = sample;
    
    data.push_back(sample);

    return sample;
}

bool RandomDataGenerator::EndOfData()
{
    return (int)data.size() >= numBars;
}