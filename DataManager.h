#ifndef __DataManager_H__
#define __DataManager_H__

#include <string>
#include <vector>


class DataReader;

class DataManager
{
public:
    void AddData(DataReader *dataReader);
    DataReader *GetData(int index);
    int GetCount();

private:
    std::vector<DataReader *> dataReaders;
};


#endif