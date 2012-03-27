#include "DataReader.h"


double DataReader::GetSampleAtIndex(int n)
{
    if (n >= (int)data.size())
        return 0;
    return data[n];
}

double DataReader::GetMinValueInRange(int start, int end)
{
    double min = data[start];

    for (int i = start + 1; i < end && i < (int)data.size(); ++ i)
    {
        if (data[i] < min)
            min = data[i];
    }

    return min;
}

double DataReader::GetMaxValueInRange(int start, int end)
{
    double max = data[start];

    for (int i = start + 1; i < end && i < (int)data.size(); ++ i)
    {
        if (data[i] > max)
            max = data[i];
    }

    return max;
}

void DataReader::PushDataSample(double sample)
{
    data.push_back(sample);
    timeIndex ++;
}