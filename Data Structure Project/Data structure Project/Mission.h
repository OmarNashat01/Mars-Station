#pragma once
#include"./Rover.h"

class Mission
{
private:
    char Type;
    int ID, EventDay, TargetLocation, Duration, Priotity, Completion_Day, Starting_Day, traveltime;
    Rover* rover;
  
public:
    Mission(int id, int Ed, int Tloc, int Mdur, int sig)
    {
        ID = id;
        EventDay = Ed;
        TargetLocation = Tloc;
        Duration = Mdur;
        Priotity = sig;
        rover = nullptr;
        Completion_Day = -1;
        Type = 'A';
        Starting_Day = 0;
        traveltime = 0;
    }

    void Start_Mission(Rover* &rv, int Cur_day)
    {
        rover = rv;
        Starting_Day = Cur_day;
        traveltime = 2 * (TargetLocation / rv->Get_Speed()) / 25;
        Completion_Day = Cur_day + Duration + traveltime;
    }

    int Get_Completion_Day() { return Completion_Day; }

    void Set_Type(char t) { Type = t; }
    char Get_Type() { return Type; }
    int Get_Startingday() { return Starting_Day; }
    int Get_Waiting_dur() { return Starting_Day - EventDay; }
    int Get_EventDay() { return EventDay; }


    int Get_Duration() { return Duration; }
    int Get_Execution_Duration() { return Duration + traveltime; }
    Rover* Get_Rover() { return rover; }
    int Get_ID() { return ID;  }

};
