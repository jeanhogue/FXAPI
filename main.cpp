#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "DataManager.h"
#include "CapitalManager.h"
#include "DataReader.h"
#include "CSVReader.h"
#include "RandomDataGenerator.h"
#include "IFXActor.h"
#include "Simulator.h"
#include "ObjectManager.h"
#include "MovingAverage.h"
#include "OutputIndicatorDecorator.h"
#include "MATrader.h"
#include "Renderer.h"
#include "BollingerBands.h"

DataManager dataManager;
CapitalManager capitalManager;
std::vector<IFXActor *> loadedActors;

bool GetCommand();
void LoadData(DataReader *dataReader);
void Run(std::string args);
void Cleanup();

bool USE_RENDERER = true;


int main(int argc, char **argv)
{
    atexit(Cleanup);

    capitalManager.SetFunds(10000);

    ObjectManager objectManager;

    //dataManager.AddData(new CSVReader("Data/Q1_3600_1000.csv", t1H));
    dataManager.AddData(new RandomDataGenerator(1.20, 150));

    //loadedActors.push_back(new OutputIndicatorDecorator(CreateMA(tSMA, 3), "MA_test.txt"));
    //loadedActors.push_back(new MATrader(&capitalManager, &objectManager));
    loadedActors.push_back(new BollingerBands(6, 1));
    
    Simulator simulator(dataManager.GetData(0), loadedActors, &capitalManager);

    simulator.Init();
    simulator.Run();

    capitalManager.PrintReport();

    if (USE_RENDERER)
    {
        Renderer renderer(&simulator, &objectManager);
        StartRendering(argc, argv, &renderer);
    }
    else
        system("PAUSE");

    return 0;
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

    /*if (command == "load")
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
    }*/

    return false;
}

void LoadData(DataReader *dataReader)
{
    dataManager.AddData(dataReader);
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

    /*Simulator simulator(dataManager.GetData(fileIndex), loadedActors, &capitalManager);
    simulator.Run();*/
}

void Cleanup()
{
    for (unsigned int i = 0; i < loadedActors.size(); ++ i)
        delete loadedActors[i];
    loadedActors.clear();
}