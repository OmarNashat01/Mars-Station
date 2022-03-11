#pragma once
#include"Event.h"
#include"MarsStation.h"

class CancellationEvent : public Event
{
public:
	CancellationEvent(MarsStation* st, int ID, int Ed);
	
	void Execute(LinkedQueue<Mission*>* missions[]);
};