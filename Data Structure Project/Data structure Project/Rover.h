#pragma once
class Rover
{  
private:
    int ID;
    int speed;
    int Missions_Before_checkup, Check_Up_Duration;
    int remaining_Missions_before_checkup;
    bool In_mission;
    char type;
    int Checkup_End_Day;
 
public:
    Rover(int sp, int Nbeforecheckup,int checkupduration, int id, char t);
    bool Is_Usable(int Duration);
    int Get_Checkup_End_Day();
    void Reset_Rover();
    int Get_ID();
    int Get_Speed();
    int Get_TimeBeforeCheckup();
    void Start_Checkup(int currday);
    char Get_Type();
    void operator = (Rover R);
};
