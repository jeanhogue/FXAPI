#ifndef __CSVREADER_H__
#define __CSVREADER_H__

#include <fstream>
#include "DataReader.h"


class CSVReader : public DataReader
{
public:
    CSVReader(std::string _filename, Timeframe timeFrame);

    virtual void Init();
    virtual void Cleanup();

    virtual double GetNextTick();

    virtual bool EndOfData();

private:
    std::ifstream in;
    std::string filename;

    char buffer[256];
};

#endif