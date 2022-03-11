#include"FormulationEvent.h"

FormulationEvent::FormulationEvent(MarsStation* st, int id, int Ed, char type, int Tloc, int Mdur, int sig):Event(st,id,Ed)
{
    Type = type;
    TargetLocation = Tloc;
    Duration = Mdur;
    Priotity = sig;
}

void FormulationEvent::Execute(LinkedQueue<Mission*>* missions[])
{
	Mission* m = new Mission(ID, EventDay, TargetLocation, Duration, Priotity);
	m->Set_Type(Type);
    switch (Type)
    {
        case('M'):
        {
            missions[Mountain]->enqueue(m);
            break;
        }
        case('E'):
        {
            missions[Emergency]->enqueue(m);
            break;
        }
        case('P'):
        {
            missions[Polar]->enqueue(m);
            break;
        }
    }

}
