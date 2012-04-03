#ifndef __Simulator_H__
#define __Simulator_H__

#include <string>
#include <vector>
#include "IFXActor.h"
#include "DataReader.h"


class CapitalManager;

class Simulator
{
public:
    Simulator(DataReader *_reader, std::vector<IFXActor *> _actors, CapitalManager *_capitalManager);
    
    void Init();

    void Run();
    void RunOneBar();

    void Cleanup();

    void GoForwardNBars(int nBars, int numBarsToDraw);
    void GoBackNBars(int nBars);

    bool GoToPreviousOrder();
    bool GoToNextOrder();

    std::vector<IFXActor *> GetActors() { return actors; }
    DataReader *GetDataReader() { return reader; }

    double GetCurrentSample() { return currentSample; }
    int GetCurrentIndex() { return currentIndex - 1; }

private:
    DataReader *reader;
    std::vector<IFXActor *> actors;
    CapitalManager *capitalManager;

    double currentSample;
    int currentIndex;
    int currentOrder;
};


#endif