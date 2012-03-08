#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "DataManager.h"
#include "IFXActor.h"
#include "Simulator.h"
#include "MovingAverage.h"

DataManager dataManager;
std::vector<IFXActor *> loadedActors;

void SetupActors();
bool GetCommand();
void LoadData(std::string filename);
void Run(std::string args);


int main()
{
    SetupActors();

    bool stop;

    do 
    {
        stop = GetCommand();
    } 
    while(!stop);

    return 0;
}

void SetupActors()
{
    // a change in any actor will require recompilation; in the future
    // it might be desirable to make this more dynamic to allow easier scripting

    loadedActors.push_back(new MovingAverage(12));
}

bool GetCommand()
{
    std::string fullCommand;
    std::cin >> fullCommand;

    if (fullCommand == "q" || fullCommand == "Q")
        return true;

    std::string command, args;

    size_t pos = fullCommand.find(' ');
    if (pos == std::string::npos)
    {
        command = fullCommand;
    }
    else
    {
        command = fullCommand.substr(0, pos);
        args = fullCommand.substr(pos);
    }

    if (command == "load")
    {
        LoadData(args);
    }
    else if (command == "run")
    {
        Run(args);
    }
    else
    {
        std::cout << "Unknown command: " << fullCommand << std::endl;
    }

    return false;
}

void LoadData(std::string filename)
{
    dataManager.AddData(filename);
}

void Run(std::string args)
{
    // if args is empty, use data file index 0
    // else args should equal the index of the data file to use

    int fileIndex = 0;
    if (!args.empty())
    {
        std::stringstream ss;
        ss << args;
        ss >> fileIndex;
        if (fileIndex < 0 || fileIndex >= dataManager.GetCount())
        {
            std::cout << "Error with the requested data file" << std::endl;
            return;
        }
    }

    Simulator simulator(dataManager.GetData(fileIndex), loadedActors);
    simulator.Run();
}