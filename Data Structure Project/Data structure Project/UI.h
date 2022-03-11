#pragma once
#include<iostream>
#include<fstream>
#include"Lists/LinkedQueue.h"

class MarsStation;
class Event;
class Mission;
class Rover;


class UI
{  
protected:
    MarsStation* Station;
  
public:
    UI(MarsStation* st) { Station = st; }
    
    virtual int Get_Mode_of_Operation() { return -1; }
    virtual bool Read_In_file() { return false; }
    virtual void Print_Day() {}
    virtual void Print(std::string message) {}
    virtual void Get_Input() {}
    virtual void Create_Out_file() {};
    virtual void Mission_Failed() {}
    virtual LinkedQueue<Rover*>* Get_Rovers(char c) { return nullptr; }
    virtual LinkedQueue<Event*>* Get_Events() { return nullptr; }
    virtual int Get_AutoP() { return 0; }
    virtual int Get_Last_ED() { return 0; }
};
