#pragma once
#include"UI.h"
#include"MarsStation.h"


class Output : public UI
{ 
public:
    Output(MarsStation* st);

    void Print_Day();
    void Print(std::string message);
    void Create_Out_file();
    void Mission_Failed();
};
