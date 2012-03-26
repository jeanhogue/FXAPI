#include <cassert>
#include "Simulator.h"
#include "CapitalManager.h"


Simulator::Simulator(DataReader *_reader, std::vector<IFXActor *> _actors, CapitalManager *_capitalManager)
: reader(_reader), actors(_actors), capitalManager(_capitalManager), currentIndex(0)
{
}

void Simulator::Init()
{
    for (unsigned int i = 0; i < actors.size(); ++ i)
        actors[i]->Init();
}

void Simulator::Run()
{    
    do 
    {
        RunOneBar();
    }
    while (!reader->EndOfData());

    capitalManager->CloseAllOrders();
}

void Simulator::RunOneBar()
{
    currentSample = reader->GetNextTick();
    for (unsigned int i = 0; i < actors.size(); ++ i)
        actors[i]->OnNewBar(currentSample, currentIndex);

    capitalManager->OnNewBar(currentSample, currentIndex);

    currentIndex ++;
}

void Simulator::GoForwardNBars(int nBars)
{
    currentIndex += nBars;
 }

void Simulator::GoBackNBars(int nBars)
{
    if (currentIndex > nBars)
        currentIndex -= nBars;
    else
        currentIndex = 0;
}