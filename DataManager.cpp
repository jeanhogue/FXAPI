#include <fstream>
#include <iostream>
#include <cassert>
#include "DataManager.h"


void DataManager::AddData(std::string filename)
{
    // make sure the file exists
    std::ifstream in(filename.c_str());
    bool valid = in.is_open();
    in.close();

    if (!valid)
        std::cout << "Filename " << filename << " is not valid; skipping" << std::endl;
    else
        dataFiles.push_back(filename);
}

std::string DataManager::GetData(int index)
{
    assert(index > 0 && index <= (int)dataFiles.size());
    return dataFiles[index];
}

int DataManager::GetCount() 
{ 
    return (int)dataFiles.size(); 
}