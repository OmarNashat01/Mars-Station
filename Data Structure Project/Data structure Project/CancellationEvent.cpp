#include"CancellationEvent.h"

CancellationEvent::CancellationEvent(MarsStation* st, int ID, int Ed) : Event(st,ID,Ed)
{}


void CancellationEvent::Execute(LinkedQueue<Mission*>* missions[])
{
	LinkedQueue<Mission*> tmp;
	Mission* m;
	
	// dequeue the whole missions list in a temp queue and check if you find the mission required for cancellation 
	// delete it and proceed to empty the missions queue, at the end return the tmp queue to the missions queue
	while (missions[Mountain]->dequeue(m))
	{
		if (m->Get_ID() != ID)   // if the missions is not the mission required for cancellation enqueue in tmp
			tmp.enqueue(m);
		else                    // else delete the mission
			delete m;
	}
	while (tmp.dequeue(m))
		missions[Mountain]->enqueue(m);


	// uncomment the following part to make the cancellation event able to cancel any mission type not only mountainuos missions
	/*while (missions[Emergency]->dequeue(m))
	{
		if (m->Get_ID() != ID)
			tmp.enqueue(m);
		else
			delete m;
	}
	while (tmp.dequeue(m))
		missions[Emergency]->enqueue(m);

	while (missions[Polar]->dequeue(m))
	{
		if (m->Get_ID() != ID)
			tmp.enqueue(m);
		else
			delete m;
	}
	while (tmp.dequeue(m))
		missions[Polar]->enqueue(m);*/


}