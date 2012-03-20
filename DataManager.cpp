#include <iostream>
#include <cassert>
#include "DataManager.h"
#include "DataReader.h"


void DataManager::AddData(DataReader *dataReader)
{
    if (!dataReader->IsValidReader())
        std::cout << "Data Reader " << dataReader->GetStr() << " is not valid; skipping" << std::endl;
    else
        dataReaders.push_back(dataReader);
}

DataReader *DataManager::GetData(int index)
{
    assert(index >= 0 && index <= (int)dataReaders.size());
    return dataReaders[index];
}

int DataManager::GetCount() 
{ 
    return (int)dataReaders.size(); 
}