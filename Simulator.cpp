#include "Simulator.h"
#include <cassert>


Simulator::Simulator(std::string filename, std::vector<IFXActor *> _actors)
: in(filename.c_str()), actors(_actors)
{
    assert(in.is_open());
}

Simulator::~Simulator()
{
    in.close();
}

void Simulator::Run()
{
    for (unsigned int i = 0; i < actors.size(); ++ i)
        actors[i]->Init();
    
    double sample;
    do 
    {
        in >> sample;
        for (unsigned int i = 0; i < actors.size(); ++ i)
            actors[i]->OnNewBar(sample);
    }
    while(!in.eof());
}