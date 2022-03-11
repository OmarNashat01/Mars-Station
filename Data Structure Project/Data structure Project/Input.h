#pragma once
#include"UI.h"
#include"MarsStation.h"

class Input : public UI
{
private:
	int AutoP, Last_ED;
	LinkedQueue<Rover*>* Rovers[3];
	LinkedQueue<Event*>* Events;
public:
	Input(MarsStation* st);
	
	bool Read_In_file();
	int Get_Mode_of_Operation();
	void Get_Input();
	LinkedQueue<Rover*>* Get_Rovers(char c);
	LinkedQueue<Event*>* Get_Events();
	int Get_AutoP();
	int Get_Last_ED();
};
