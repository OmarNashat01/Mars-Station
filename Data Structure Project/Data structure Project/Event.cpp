#include"Event.h"

Event::Event(MarsStation* st, int id, int Ed)
{
	Station = st;
	ID = id;
	EventDay = Ed;
}

int Event::GetEventDay()
{
	return EventDay;
}
