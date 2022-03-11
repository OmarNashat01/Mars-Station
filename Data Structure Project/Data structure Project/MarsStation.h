#ifndef MARS_STATION_H
#define MARS_STATION_H

//Include this for the sleep function
//Windows
#include<Windows.h>
//Un comment this if you are using Macos or Linux and comment the upper line
//#include<unistd.h>

#include<time.h>
#include<stdlib.h>
#include<string>

#include"Defs.h"
#include"./Output.h"
#include"./Input.h"
#include"./Rover.h"
#include"./Lists/LinkedQueue.h"
#include"./FormulationEvent.h"
#include"./CancellationEvent.h"
#include"./Mission.h"
#include"Priority_Queue.h"


class MarsStation
{
private:
    UI* Out;
    UI* In;

    int Last_ED;
    int AutoP, Mode_of_Operation;
    int Current_Day;

    LinkedQueue<Event*>* Events;
    PQueue<Mission*> In_Execution_Missions;
    LinkedQueue<Mission*> Complete_Missions;

    LinkedQueue<Mission*>* Waiting_Missions[3];
    LinkedQueue<Rover*>* Waiting_Rovers[3];

    LinkedQueue<Rover*> In_Checkup_Rovers[3];
    
public:
    MarsStation();
    void Read_Data();
    void Simulate_Day();

    bool HasEnded();
    void Run();
      
    ~MarsStation();

    LinkedQueue<Mission*> Get_Missions(char c);
    LinkedQueue<Rover*> Get_Rovers(char c);
    int Get_CurrentDay();
    PQueue<Mission*>& Get_Inexexution_Missions();
;
};

#endif
