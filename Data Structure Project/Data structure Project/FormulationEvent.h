#pragma once
#include"Event.h"
#include"./MarsStation.h"

class FormulationEvent : public Event
{
private:
    int TargetLocation, Duration, Priotity;
    char Type;

public:
      FormulationEvent(MarsStation* st, int id, int Ed, char type, int Tloc, int Mdur, int sig);
      void Execute(LinkedQueue<Mission*>* missions[]);
};
