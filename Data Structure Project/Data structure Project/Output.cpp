#include"Output.h"
#include<iostream>

using namespace std;

Output::Output(MarsStation* st) : UI(st)
{}

void Output::Print_Day()
{
    cout << "Current Day: " << Station->Get_CurrentDay() << endl;

    {
		Mission* mission;
		int countM = 0, countE = 0, countP = 0;

		LinkedQueue<Mission*> Waiting_M(Station->Get_Missions('M'));
		LinkedQueue<Mission*> Waiting_E(Station->Get_Missions('E'));
		LinkedQueue<Mission*> Waiting_P(Station->Get_Missions('P'));

		string msg = "";

		if (Waiting_E.peak(mission))
			msg += "[";
		while (Waiting_E.dequeue(mission))
		{
			countE++;
			msg += to_string(mission->Get_ID()) + ",";
			if (!Waiting_E.peak(mission))
			{
				msg = msg.substr(0,msg.length() -1);
				msg += "]";
			}
		}

		if (Waiting_P.peak(mission))
			msg += " (";
		while (Waiting_P.dequeue(mission))
		{
			countP++;
			msg += to_string(mission->Get_ID()) + ",";
			if (!Waiting_P.peak(mission))
			{
				msg = msg.substr(0,msg.length() -1);
				msg += ")";
			}
		}

		if (Waiting_M.peak(mission))
			msg += " {";
		while (Waiting_M.dequeue(mission))
		{
			countM++;
			msg += to_string(mission->Get_ID()) + ",";
			if (!Waiting_M.peak(mission))
			{
				msg = msg.substr(0,msg.length() -1);
				msg += "}";
			}
		}

		cout << countP + countE + countM << " Waiting Missions: " << msg << endl;
    }
    cout << "-------------------------------------------------------\n";
    {
		Mission* mission;
		int countME = 0;
		string msgE = "", msgP = "", msgM = "";
		PQueue<Mission*> Execution_Mission(Station->Get_Inexexution_Missions());

		while (Execution_Mission.dequeue(mission))
		{
			if (mission->Get_Type() == 'E')
			{
			msgE += to_string(mission->Get_ID()) + "/" 
				+ to_string(mission->Get_Rover()->Get_ID()) + ", " ;
			}
			else if (mission->Get_Type() == 'P')
			{
			msgP += to_string(mission->Get_ID()) + "/" 
				+ to_string(mission->Get_Rover()->Get_ID()) + ", " ;
			}
			else if (mission->Get_Type() == 'M')
			{
			msgM += to_string(mission->Get_ID()) + "/" 
				+ to_string(mission->Get_Rover()->Get_ID()) + ", " ;
			}
			countME++;
		}
	
		if (msgE != "")
		{
			msgE = "[" + msgE.substr(0, msgE.length()-2) + "] ";
		}
		if (msgP != "")
		{
			msgP = "(" + msgP.substr(0, msgP.length()-2) + ") ";
		}
		if (msgM != "")
		{
			msgM = "{" + msgM.substr(0, msgM.length()-2) + "}";
		}

		cout  << countME << " In-Execution Missions/Rovers: " << msgE << msgP << msgM << endl;
    }
    cout << "-------------------------------------------------------\n";

    {
		int countM = 0, countE = 0, countP = 0;
		LinkedQueue<Rover*> Waiting_M(Station->Get_Rovers('M'));
		LinkedQueue<Rover*> Waiting_E(Station->Get_Rovers('E'));
		LinkedQueue<Rover*> Waiting_P(Station->Get_Rovers('P'));

		Rover* rv;
		string msg = "";

		if (Waiting_E.peak(rv))
			msg += "[";
		while (Waiting_E.dequeue(rv))
		{
			countM++;
			msg += to_string(rv->Get_ID()) + ",";
			if (!Waiting_E.peak(rv))
			{
				msg = msg.substr(0,msg.length() -1);
				msg += "]";
			}
		}

		if (Waiting_P.peak(rv))
			msg += " (";
		while (Waiting_P.dequeue(rv))
		{
			countE++;
			msg += to_string(rv->Get_ID()) + ",";
			if (!Waiting_P.peak(rv))
			{
				msg = msg.substr(0,msg.length() -1);
				msg += ")";
			}
		}

		if (Waiting_M.peak(rv))
			msg += " {";
		while (Waiting_M.dequeue(rv))
		{
			countP++;
			msg += to_string(rv->Get_ID()) + ",";
			if (!Waiting_M.peak(rv))
			{
				msg = msg.substr(0,msg.length() -1);
				msg += "}";
			}
		}

		cout << countP + countE + countM << " Available Rovers: " << msg << endl;
    }
    cout << "-------------------------------------------------------\n";

    {
		int countM = 0, countE = 0, countP = 0;
		LinkedQueue<Rover*> In_checkup_M(Station->Get_Rovers('m'));
		LinkedQueue<Rover*> In_checkup_E(Station->Get_Rovers('e'));
		LinkedQueue<Rover*> In_checkup_P(Station->Get_Rovers('p'));

		Rover* rv;
		string msg = "";

		if (In_checkup_E.peak(rv))
			msg += "[";
		while (In_checkup_E.dequeue(rv))
		{
			countM++;
			msg += to_string(rv->Get_ID()) + ",";
			if (!In_checkup_E.peak(rv))
			{
			msg = msg.substr(0,msg.length() -1);
			msg += "]";
			}
		}

		if (In_checkup_P.peak(rv))
			msg += " (";
		while (In_checkup_P.dequeue(rv))
		{
			countE++;
			msg += to_string(rv->Get_ID()) + ",";
			if (!In_checkup_P.peak(rv))
			{
			msg = msg.substr(0,msg.length() -1);
			msg += ")";
			}
		}

		if (In_checkup_M.peak(rv))
			msg += " {";
		while (In_checkup_M.dequeue(rv))
		{
			countP++;
			msg += to_string(rv->Get_ID()) + ",";
			if (!In_checkup_M.peak(rv))
			{
				msg = msg.substr(0,msg.length() -1);
				msg += "}";
			}
		}

		cout << countP + countE + countM << " In-Checkup Rovers: " << msg << endl;
    }
    cout << "-------------------------------------------------------\n";

    {
		Mission* mission;
		int countME = 0;
		string msgE = "", msgP = "", msgM = "";
		LinkedQueue<Mission*> Complete_Mission(Station->Get_Missions('C'));

		while (Complete_Mission.dequeue(mission))
		{
			if (mission->Get_Type() == 'E')
			{
				msgE += to_string(mission->Get_ID()) + ", " ;
			}
			else if (mission->Get_Type() == 'P')
			{
				msgP += to_string(mission->Get_ID()) + ", " ;
			}
			else if (mission->Get_Type() == 'M')
			{
				msgM += to_string(mission->Get_ID()) + ", " ;
			}
			countME++;
		}
	
		if (msgE != "")
		{
			msgE = "[" + msgE.substr(0, msgE.length()-2) + "] ";
		}
		if (msgP != "")
		{
			msgP = "(" + msgP.substr(0, msgP.length()-2) + ") ";
		}
		if (msgM != "")
		{
			msgM = "{" + msgM.substr(0, msgM.length()-2) + "}";
		}

		cout  << countME << " Complete Missions: " << msgE << msgP << msgM << endl;
    }
	cout << endl << endl;
}

void Output::Create_Out_file()
{
    ofstream file("../Mars Station.txt", ios::out);

    if (!file)
    {
        cout << "Failed to open file for writing..\n";
        return;
    }

	// If 
	if (Station->Get_CurrentDay() == -1)
	{
		file << "Not enough rovers to complete the missions.";
		file.close();
		return;
	}


    file << "CD\tID\tFD\tWD\tED\n";
    Mission* msn;
    Rover* rv;
    int countMM = 0, countME = 0, countMP = 0;
	int countRM = 0, countRE = 0, countRP = 0;
    int sum_wait = 0, sum_dur = 0;
	LinkedQueue<Mission*> complete(Station->Get_Missions('C'));
    while (complete.dequeue(msn))
    {
        if (msn->Get_Type() == 'M')
            countMM++;
        if (msn->Get_Type() == 'E')
            countME++;
        if (msn->Get_Type() == 'P')
            countMP++;
        sum_wait += msn->Get_Waiting_dur();
        sum_dur += msn->Get_Execution_Duration();
        file << msn->Get_Completion_Day() << "      "
            << msn->Get_ID() << "       "
            << msn->Get_EventDay() << "      "
            << msn->Get_Waiting_dur() << "       "
            << msn->Get_Execution_Duration() << endl;
    }
    countRM = 0; countRE= 0; countRP = 0;
	LinkedQueue<Rover*> waiting_roversM(Station->Get_Rovers('M'));
	LinkedQueue<Rover*> waiting_roversE(Station->Get_Rovers('E'));
	LinkedQueue<Rover*> waiting_roversP(Station->Get_Rovers('P'));

    while (waiting_roversM.dequeue(rv))
    {
        countRM++;
    }
	while (waiting_roversE.dequeue(rv))
	{
		countRE++;
	}
	while (waiting_roversP.dequeue(rv))
	{
		countRP++;
	}

	file << "-----------------------------------------------\n";
	file << "-----------------------------------------------\n";
    file << "Missions: " << countMM + countME + countMP << "[M: " << countMM
        << ", P: " << countMP << ", E: " << countME << "]\n";
    file << "Rovers " << countRM + countRE+ countRP
        << "[M: " << countRM << ", P: " << countRP
        << ", E: " << countRE << "]\n";
	if (sum_wait == 0)
		file << "Avg Wait = " << 0 << ", Avg Exec = " << 0 << endl;
	else
		file << "Avg Wait = " << (float(sum_wait) / (countMM + countME + countMP))
			<< ", Avg Exec = " << (float(sum_dur) / (countMM + countME + countMP)) << endl;

    file.close();
	cout << "Simulation ends, OutPut file created\n";

}

void Output::Mission_Failed()
{
	cout << "\n=========================================================\nMission has failed and is now being re-formulated again.\n=========================================================\n\n";
}

void Output::Print(string message)
{
    cout << message << endl;
}
