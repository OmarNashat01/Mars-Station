#pragma once
#include"./Mission.h"
#include"Lists/LinkedQueue.h"

class MarsStation;

class Event
{
protected:
    int ID, EventDay;
    MarsStation* Station;

public:
    Event(MarsStation* st, int id, int Ed);
    int GetEventDay();
    virtual void Execute(LinkedQueue<Mission*>* missions[]) = 0;

};
