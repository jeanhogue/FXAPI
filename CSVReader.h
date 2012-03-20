#ifndef __CSVREADER_H__
#define __CSVREADER_H__

#include <fstream>
#include <string>
#include <vector>
#include "DataReader.h"


class CSVReader : public DataReader
{
public:
    CSVReader(std::string _filename, Timeframe timeFrame);

    virtual double GetNextTick();

    virtual bool IsValidReader();
    virtual bool EndOfData();

    virtual double GetSampleNBarsAgo(int n);

    virtual double GetMinValueInRange(int start, int end);
    virtual double GetMaxValueInRange(int start, int end);

    virtual std::string GetStr();

private:
    std::ifstream in;
    std::string filename;

    char buffer[256];
    std::vector<double> data;
};

#endif