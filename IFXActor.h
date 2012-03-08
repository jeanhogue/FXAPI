#ifndef __IFXActor_H__
#define __IFXActor_H__


class IFXActor 
{
public:
    virtual void Init() = 0;
    virtual void OnNewBar(double sample) = 0;
};

#endif