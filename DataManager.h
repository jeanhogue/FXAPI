#ifndef __DataManager_H__
#define __DataManager_H__

#include <string>
#include <vector>


class DataManager
{
public:
    void AddData(std::string filename);
    std::string GetData(int index);
    int GetCount();

private:
    std::vector<std::string> dataFiles;
};


#endif