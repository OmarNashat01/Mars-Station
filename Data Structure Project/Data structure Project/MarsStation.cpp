#include"./MarsStation.h"
using namespace std;
 
 

MarsStation::MarsStation()
{
    AutoP = 10000;
    Current_Day = 1;
    Out = new Output(this);
    In = new Input(this);

    for (int i = 0; i < 3; i++)
    {
        Waiting_Missions[i] = new LinkedQueue<Mission*>;
    }

    
    Read_Data();

    Out->Print("Please Enter Mode of Operation:\n1- Interactive.\n2- Step-By-Step.\n3- Silent. ");
    Mode_of_Operation = In->Get_Mode_of_Operation();

    if (Mode_of_Operation - 1 == Silent)
        Out->Print("Silent Mode\nSimulation Starts...");
}

void MarsStation::Read_Data()
{ 
    Out->Print("Please Enter file name without the extension (\".txt\") or enter default for the default input file");
    if (!In->Read_In_file())
    {
        Out->Print("File not found.. Exiting simulation");
        exit(1);
    }

    Waiting_Rovers[Mountain] = In->Get_Rovers('M');
    Waiting_Rovers[Emergency] = In->Get_Rovers('E');
    Waiting_Rovers[Polar] = In->Get_Rovers('P');

    if (Waiting_Rovers[Polar]->IsEmpty() || (Waiting_Rovers[Mountain]->IsEmpty() && Waiting_Rovers[Emergency]->IsEmpty()))
    {
        Out->Print("Not enough rovers to complete the missions.. Exiting simulation");
        Current_Day = -1;
        Out->Create_Out_file();
        exit(1);
    }

    Events = In->Get_Events();
    AutoP = In->Get_AutoP();
}

void MarsStation::Simulate_Day()
{
    // Main While loop with each entrance of the loop represents a new day
    Event* event;
    Mission* mission;
    Rover* rover;

    // Check For the events that should be formulated today and formulate them
    while (Events->peak(event))
    {
        if (event->GetEventDay() == Current_Day)
        {
            Events->dequeue(event);
            event->Execute(Waiting_Missions);
        }
        else
            break;
    }

    // Start by Checking for the rovers that finished the checkup and return them to their original list so they can work in the same day
    // Type represents 0--> Mountain , 1--> Emergency, 2--> Polar
    for (int Type = 0; Type < 3; Type++)
    {
        while (In_Checkup_Rovers[Type].peak(rover))
        {
            if (rover->Get_Checkup_End_Day() == Current_Day)
            {
                In_Checkup_Rovers[Type].dequeue(rover);
                rover->Reset_Rover();
                Waiting_Rovers[Type]->enqueue(rover);
            }
            else
                break;
        }
    }
    

    // Then assign Emergency missions 
    while (!Waiting_Missions[Emergency]->IsEmpty())
    {
        if (!Waiting_Rovers[Emergency]->IsEmpty())
        {
            Waiting_Missions[Emergency]->dequeue(mission);
            Waiting_Rovers[Emergency]->dequeue(rover);

            mission->Start_Mission(rover, Current_Day);
            In_Execution_Missions.enqueue(mission, mission->Get_Completion_Day());
        }
        else if (!Waiting_Rovers[Mountain]->IsEmpty())
        {
            Waiting_Missions[Emergency]->dequeue(mission);
            Waiting_Rovers[Mountain]->dequeue(rover);

            mission->Start_Mission(rover, Current_Day);
            In_Execution_Missions.enqueue(mission, mission->Get_Completion_Day());
        }
        else if (!Waiting_Rovers[Polar]->IsEmpty())
        {
            Waiting_Missions[Emergency]->dequeue(mission);
            Waiting_Rovers[Polar]->dequeue(rover);

            mission->Start_Mission(rover, Current_Day);
            In_Execution_Missions.enqueue(mission, mission->Get_Completion_Day());
        }
        else
            break;
    }

    // Then assign the Polar missions
    while (!Waiting_Missions[Polar]->IsEmpty())
    {
        if (!Waiting_Rovers[Polar]->IsEmpty())
        {
            Waiting_Missions[Polar]->dequeue(mission);
            Waiting_Rovers[Polar]->dequeue(rover);

            mission->Start_Mission(rover, Current_Day);
            In_Execution_Missions.enqueue(mission, mission->Get_Completion_Day());
        }
        else
            break;
    }

    // Then assign Mountain missions
    while (!Waiting_Missions[Mountain]->IsEmpty())
    {
        if (!Waiting_Rovers[Mountain]->IsEmpty())
        {
            Waiting_Missions[Mountain]->dequeue(mission);
            Waiting_Rovers[Mountain]->dequeue(rover);

            mission->Start_Mission(rover, Current_Day);
            In_Execution_Missions.enqueue(mission, mission->Get_Completion_Day());
        }
        else if (!Waiting_Rovers[Emergency]->IsEmpty())
        {
            Waiting_Missions[Mountain]->dequeue(mission);
            Waiting_Rovers[Emergency]->dequeue(rover);

            mission->Start_Mission(rover, Current_Day);
            In_Execution_Missions.enqueue(mission, mission->Get_Completion_Day());
        }
        else
            break;
    }



    // Start by checking for done missions
    while (In_Execution_Missions.peak(mission))
    {
        if (mission->Get_Completion_Day() == Current_Day)
        {
            In_Execution_Missions.dequeue(mission);
            
            //Mission Failure Part
            srand(time(nullptr)+ Current_Day + mission->Get_ID());
            int success = rand() % (8 * (mission->Get_Rover()->Get_TimeBeforeCheckup())) + 1;
            if (success == 2)
            {
                if (Mode_of_Operation - 1 == Interactive || Mode_of_Operation - 1 == Step_By_Step)
                    Out->Mission_Failed();

                rover = mission->Get_Rover();
                rover->Start_Checkup(Current_Day);
                if (mission->Get_Type() == 'M')
                {
                    Waiting_Missions[Mountain]->enqueue(mission);
                }
                else if (mission->Get_Type() == 'E')
                {
                    Waiting_Missions[Emergency]->enqueue(mission);
                }
                else if (mission->Get_Type() == 'P')
                {
                    Waiting_Missions[Polar]->enqueue(mission);
                }


                if (rover->Get_Type() == 'M')
                {
                    In_Checkup_Rovers[Mountain].enqueue(rover);
                }
                else if (rover->Get_Type() == 'E')
                {
                    In_Checkup_Rovers[Emergency].enqueue(rover);
                }
                else if (rover->Get_Type() == 'P')
                {
                    In_Checkup_Rovers[Polar].enqueue(rover);
                }

            }
            else
            {
                Complete_Missions.enqueue(mission);

                // Free the rover and check if its usable or needs check up first
                rover = mission->Get_Rover();
                if (rover->Is_Usable(Current_Day))
                {
                    if (rover->Get_Type() == 'M')
                    {
                        Waiting_Rovers[Mountain]->enqueue(rover);
                    }
                    else if (rover->Get_Type() == 'E')
                    {
                        Waiting_Rovers[Emergency]->enqueue(rover);
                    }
                    else if (rover->Get_Type() == 'P')
                    {
                        Waiting_Rovers[Polar]->enqueue(rover);
                    }
                }
                else
                {
                    if (rover->Get_Type() == 'M')
                    {
                        In_Checkup_Rovers[Mountain].enqueue(rover);
                    }
                    else if (rover->Get_Type() == 'E')
                    {
                        In_Checkup_Rovers[Emergency].enqueue(rover);
                    }
                    else if (rover->Get_Type() == 'P')
                    {
                        In_Checkup_Rovers[Polar].enqueue(rover);
                    }
                }
            }
        }
        else
        {
            break;
        }
    }

    Current_Day++;
}

void MarsStation::Run()
{
    while (!HasEnded())
    {
        Simulate_Day();
        if (Mode_of_Operation - 1 == Interactive)
        {
            In->Get_Input();
            Out->Print_Day();
        }
        else if (Mode_of_Operation - 1 == Step_By_Step)
        {
            Sleep(1000);
            Out->Print_Day();
        }
    }
    Rover* rv;
    
    // Return Rovers from checkup to their lists for easier output file
    for (int type = 0; type < 3; type++)
    {
        while (In_Checkup_Rovers[type].dequeue(rv))
        {
            Waiting_Rovers[type]->enqueue(rv);
        }
    }
    Out->Create_Out_file();
}


bool MarsStation::HasEnded()
{
    if (Events->IsEmpty() && Waiting_Missions[Emergency]->IsEmpty() && Waiting_Missions[Mountain]->IsEmpty()
        && Waiting_Missions[Polar]->IsEmpty() && In_Execution_Missions.IsEmpty())
        return true;

    return false;
}

MarsStation::~MarsStation()
{
    delete In;
    delete Out;

    Mission* msn;
    Rover* rv;

    if (Events)
        delete Events;

    while (Complete_Missions.dequeue(msn))
    {
	    delete msn;
    }

    while (Waiting_Rovers[Emergency]->dequeue(rv))
    {
	    delete rv;
    }
    delete Waiting_Missions[Emergency];

    while (Waiting_Rovers[Mountain]->dequeue(rv))
    {
	    delete rv;
    }
    delete Waiting_Missions[Mountain];

    while (Waiting_Rovers[Polar]->dequeue(rv))
    {
	    delete rv;
    }
    delete Waiting_Missions[Polar];

    while (In_Checkup_Rovers[Emergency].dequeue(rv))
    {
	    delete rv;
    }
    while (In_Checkup_Rovers[Mountain].dequeue(rv))
    {
	    delete rv;
    }
    while (In_Checkup_Rovers[Polar].dequeue(rv))
    {
	    delete rv;
    }
}

LinkedQueue<Mission*> MarsStation::Get_Missions(char c)
{
    if (c == 'M')
        return *Waiting_Missions[Mountain];
    else if (c == 'E')
        return *Waiting_Missions[Emergency];
    else if (c == 'P')
        return *Waiting_Missions[Polar];
    else
        return Complete_Missions;
}

LinkedQueue<Rover*> MarsStation::Get_Rovers(char c)
{
    if (c == 'M')
        return *Waiting_Rovers[Mountain];
    else if (c == 'E')
        return *Waiting_Rovers[Emergency];
    else if (c == 'P')
        return *Waiting_Rovers[Polar];
    else if (c == 'm') // m small for in checkup Mountain rovers
        return In_Checkup_Rovers[Mountain];
    else if (c == 'e') // e small for in checkup Emergency rovers
        return In_Checkup_Rovers[Emergency];
    else 
        return In_Checkup_Rovers[Polar];
}

int MarsStation::Get_CurrentDay()
{
    return Current_Day;
}

PQueue<Mission*>& MarsStation::Get_Inexexution_Missions()
{
    return In_Execution_Missions;
}
