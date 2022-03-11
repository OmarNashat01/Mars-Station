#include "Rover.h"

Rover::Rover(int sp, int Nbeforecheckup, int checkupduration, int id, char t)
{
    speed = sp;
    Missions_Before_checkup = Nbeforecheckup;
    Check_Up_Duration = checkupduration;
    In_mission = false;
    remaining_Missions_before_checkup = Missions_Before_checkup;
    type = t;
    Checkup_End_Day = 0;
    ID = id;
}

bool Rover::Is_Usable(int Current_Day)
{
    // We chech if the rover is usable after finishing the mission so we decrement the remaining_missions_before_checkup
    remaining_Missions_before_checkup -= 1;

    if (remaining_Missions_before_checkup > 0)
        return true;
    else // rover will enter checkup in the same day so the end checkup day is calculated here 
    {
	    Checkup_End_Day = Current_Day + Check_Up_Duration;
        return false;
    }
}

int Rover::Get_Checkup_End_Day()
{
    return Checkup_End_Day;
}

void Rover::Reset_Rover()
{
    remaining_Missions_before_checkup = Missions_Before_checkup;
}

void Rover::operator= (Rover R)
{
    speed = R.speed;
    Missions_Before_checkup = R.Missions_Before_checkup;
    Check_Up_Duration = R.Check_Up_Duration;
}

int Rover::Get_ID()
{
    return ID;
}

int Rover::Get_Speed()
{
    return speed;
}

int Rover::Get_TimeBeforeCheckup()
{
    return remaining_Missions_before_checkup;
}

void Rover::Start_Checkup(int currday) // Used if the rover failed to send it to check up immediately regardless of the remaining_missions_before_checkup
{
    Checkup_End_Day = currday + Check_Up_Duration;
}

char Rover::Get_Type()
{
    return type;
}
