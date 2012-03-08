#ifndef __Simulator_H__
#define __Simulator_H__

#include <string>
#include <vector>
#include <fstream>
#include "IFXActor.h"


class Simulator
{
public:
    Simulator(std::string filename, std::vector<IFXActor *> _actors);
    ~Simulator();
    void Run();

private:
    std::ifstream in;
    std::vector<IFXActor *> actors;
};


#endif