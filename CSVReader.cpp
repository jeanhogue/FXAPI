#include "CSVReader.h"
#include <cassert>
#include <cmath>


CSVReader::CSVReader(std::string _filename, Timeframe timeFrame)
: DataReader(timeFrame), filename(_filename)
{
    in.open(filename.c_str());
    assert(in.is_open());

    in.getline(buffer, 256);   // read the header
}

double CSVReader::GetNextTick()
{
    in.getline(buffer, 256);

    // use CLOSE as tick price (5th column)
    int colIndex = 0;
    int begin, end;
    for (int i = 0; i < 256; ++ i)
    {
        if (buffer[i] == ';')
        {
            colIndex ++;
            if (colIndex == 4)
                begin = i + 1;
            else if (colIndex == 5)
            {
                end = i;
                break;
            }
        }
    }

    buffer[end] = '\0';
    double sample = atof(buffer + begin);
    buffer[end] = ';';

    data.push_back(sample);

    return sample;
}

bool CSVReader::IsValidReader()
{
    return in.is_open();
}

bool CSVReader::EndOfData()
{
    return in.eof();
}

double CSVReader::GetSampleNBarsAgo(int n)
{
    int len = (int)data.size();
    if (n >= len)
        return 0;
    return data[len - 1 - n];
}

double CSVReader::GetMinValueInRange(int start, int end)
{
    int count = 0;
    double min = HUGE_VAL;

    for (int i = (int)data.size() - 1 - start; count < end - start && i >= 0; -- i, ++ count)
    {
        if (data[i] < min)
            min = data[i];
    }

    return min;
}

double CSVReader::GetMaxValueInRange(int start, int end)
{
    int count = 0;
    double max = -HUGE_VAL;

    for (int i = (int)data.size() - 1 - start; count < end - start && i >= 0; -- i, ++ count)
    {
        if (data[i] > max)
            max = data[i];
    }

    return max;
}

std::string CSVReader::GetStr()
{
    return filename;
}