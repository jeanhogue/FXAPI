#include <vector>
#include <iostream>
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

std::vector<IFXActor *> loadedActors;

Optimizable *FindOptimizable(std::vector<IFXActor *> actors);
void Cleanup();

bool OPTIMIZE = false;


int main(int argc, char **argv)
{
    atexit(Cleanup);

    CapitalManager capitalManager;

    ObjectManager objectManager;
    double bestReturn = 0;

    //DataReader *reader = new CSVReader("Data/Q1_3600_1000.csv", t1H);
    RandomDataGenerator reader(1.20, 10000, 1337);

    //loadedActors.push_back(new OutputIndicatorDecorator(CreateMA(tSMA, 3), "MA_test.txt"));
    loadedActors.push_back(new MATrader(&capitalManager, &objectManager));
    //loadedActors.push_back(new BollingerBands(20, 2));

    Simulator simulator(&reader, loadedActors, &capitalManager);

    Optimizable *optimizable = FindOptimizable(loadedActors);

    if (OPTIMIZE && optimizable)
    {
        while (optimizable->HasMoreParamsToTry())
        {
            optimizable->PrintParameters();

            simulator.Init();
            simulator.Run();
            if (capitalManager.GetFunds() > bestReturn)
            {
                optimizable->SaveParameters();
                bestReturn = capitalManager.GetFunds();
            }
            optimizable->UpdateParameters();

            simulator.Cleanup();
        }

        std::cout << std::endl << std::endl << std::endl;
        std::cout << " *** Best Parameters *** " << std::endl << std::endl;
        optimizable->SetBestParams();
        optimizable->PrintParameters();
        simulator.Init();
        simulator.Run();

        std::cout << std::endl;

        system("PAUSE");            
    }
    else
    {
        simulator.Init();
        simulator.Run();

        Renderer renderer(&simulator, &objectManager);
        StartRendering(argc, argv, &renderer);
    }
        
    return 0;
}

Optimizable *FindOptimizable(std::vector<IFXActor *> actors)
{
    Optimizable *optimizable = NULL;

    for (unsigned int i = 0; i < actors.size(); ++ i)
    {
        if ((optimizable = dynamic_cast<Optimizable *>(loadedActors[i])) != NULL)
            break;
    }

    return optimizable;
}

void Cleanup()
{
    for (unsigned int i = 0; i < loadedActors.size(); ++ i)
        delete loadedActors[i];
    loadedActors.clear();
}