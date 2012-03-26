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

    void GoForwardNBars(int nBars);
    void GoBackNBars(int nBars);

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
};


#endif