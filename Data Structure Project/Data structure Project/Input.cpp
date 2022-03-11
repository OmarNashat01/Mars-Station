#include"Input.h"

using namespace std;

Input::Input(MarsStation* st) : UI(st)
{
    for (int i = 0; i < 3; i++)
    {
    	Rovers[i] = new LinkedQueue<Rover*>;
    }
    Events = new LinkedQueue<Event*>;
    Last_ED = 0;
    AutoP = 0;
}

bool Input::Read_In_file()
{
    string filename;
    cin >> filename;
    if (filename == "default")
        filename = "../file.txt";
    else
        filename = "../" + filename + ".txt";
    fstream file;
    file.open(filename, ios::in);
    
    // Check if the input file exists
    if (!file)
        return false;

    int choice;
    file >> choice; // the number that will determine if the rover speed will be entered as a whole for every type or different for everysingle type
    int numM, numE, numP;
    file >> numM >> numP >> numE;
    if ((numM == 0 && numE == 0) || numP == 0)  // if we have dont have rovers enough  return and then we will exit from the MarsStation class
        return true;
    int  spM, spE, spP;
    if (choice == 1)
        file >> spM >> spP >> spE;
    int Nbefcheckup, checkupM, checkupP, checkupE;
    file >> Nbefcheckup >> checkupM >> checkupP >> checkupE;
    if (choice != 1)
    {
        if (numM > 0)
        {
            file >> spM;
            Rover* RM = new Rover(spM, Nbefcheckup, checkupM, 1, 'M');
            Rovers[Mountain]->enqueue(RM);
        }
        for (int i = 0; i < numM - 1; i++)
        {
            file >> spM;
            Rover* RM = new Rover(spM, Nbefcheckup, checkupM, i + 2, 'M');
            Rovers[Mountain]->enqueue(RM);
        }

        if (numP > 0)
        {
            file >> spP;
            Rover* RP = new Rover(spP, Nbefcheckup, checkupP, 1, 'P');
            Rovers[Polar]->enqueue(RP);

        }
        for (int i = 0; i < numP - 1; i++)
        {
            file >> spP;
            Rover* RP = new Rover(spP, Nbefcheckup, checkupP, i + 2, 'P');
            Rovers[Polar]->enqueue(RP);
        }
        if (numE > 0)
        {
            file >> spE;
            Rover* RE = new Rover(spE, Nbefcheckup, checkupE, 1, 'E');
            Rovers[Emergency]->enqueue(RE);
        }
        for (int i = 0; i < numE - 1; i++)
        {
            file >> spE;
            Rover* RE = new Rover(spE, Nbefcheckup, checkupE, i + 2, 'E');
            Rovers[Emergency]->enqueue(RE);
        }
    }
    if (choice == 1)
    {
        if (numM > 0)
        {
            Rover* RM = new Rover(spM, Nbefcheckup, checkupM, 1, 'M');
            Rovers[Mountain]->enqueue(RM);
        }
        if (numP > 0)
        {
            Rover* RP = new Rover(spP, Nbefcheckup, checkupP, 1, 'P');
            Rovers[Polar]->enqueue(RP);

        }
        if (numE > 0)
        {
            Rover* RE = new Rover(spE, Nbefcheckup, checkupE, 1, 'E');
            Rovers[Emergency]->enqueue(RE);
        }

        for (int i = 0; i < numM - 1; i++)
        {
            Rover* RM = new Rover(spM, Nbefcheckup, checkupM, i + 2, 'M');
            Rovers[Mountain]->enqueue(RM);
        }
        for (int i = 0; i < numP - 1; i++)
        {
            Rover* RP = new Rover(spP, Nbefcheckup, checkupP, i + 2, 'P');
            Rovers[Polar]->enqueue(RP);
        }
        for (int i = 0; i < numE - 1; i++)
        {
            Rover* RE = new Rover(spE, Nbefcheckup, checkupE, i + 2, 'E');
            Rovers[Emergency]->enqueue(RE);
        }
    }
    file >> AutoP;
    int NumEvents, id, Eventday = 0, Tloc, Mdur, Sig;
    char EventType, MissionType;
    file >> NumEvents;

    for (int i = 0; i < NumEvents; i++) // loop to read ell the events
    {
        Event* event;
        file >> EventType;
        switch (EventType)
        {
            case('F'):
            {
                file >> MissionType >> Eventday >> id >> Tloc >> Mdur >> Sig;
                event = new FormulationEvent(Station, id, Eventday, MissionType, Tloc, Mdur, Sig);
                Events->enqueue(event);
                break;
            }
            case('X'):
            {
                file >> Eventday >> id;
                event = new CancellationEvent(Station,id, Eventday);
                Events->enqueue(event);
                break;
            }
        }

    }
    Last_ED = Eventday;

    file.close();

    return true;
}

int Input::Get_Mode_of_Operation()
{
    int Mode_of_Operation;
    cin >> Mode_of_Operation;
    return Mode_of_Operation;
}

void Input::Get_Input()
{
    cin.ignore();
}


LinkedQueue<Rover*>* Input::Get_Rovers(char c)
{
    if (c == 'M')
	    return Rovers[Mountain];
    else if ( c == 'E')
	    return Rovers[Emergency];
    else if ( c == 'P')
	    return Rovers[Polar];
    return nullptr;
}

LinkedQueue<Event*>* Input::Get_Events()
{
    return Events;
}

int Input::Get_AutoP()
{
    return AutoP;
}

int Input::Get_Last_ED()
{
    return Last_ED;
}
