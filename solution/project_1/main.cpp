#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "inih/cpp/INIReader.h"
#include "inih/cpp/INIReader.cpp"
#include "inih/ini.h"
#include "inih/ini.c"
using namespace std;


struct Signal
{
	string color;
	int time_s;
};

class TrafficLights
{	
private:

	vector<Signal> signals{};

public:
	TrafficLights(vector<Signal> s)
	{
		signals = s;
	}

	void Start()
	{
		while (true)
		{
			for(int i = 0; i<signals.size(); i++)
			{
				
				system("clear");
				cout<<signals[i].color<<endl;
				this_thread::sleep_for(chrono::seconds(signals[i].time_s));			
			}
			for (size_t i = 0; i < 3; i++)
			{
				system("clear");
				this_thread::sleep_for(chrono::milliseconds(600));	
				cout<<signals[2].color<<endl;
				this_thread::sleep_for(chrono::milliseconds(600));	
			}		

		
		}
	}
};


int main()
{
	
	INIReader reader("../timings.ini");
	if (reader.ParseError() < 0) {
        std::cout << "Can't load 'timings.ini'\n";
        return 1;
    }

	int redt = reader.GetInteger("timings", "red", 4), 
	greent = reader.GetInteger("timings", "green", 1),
	yellowt = reader.GetInteger("timings", "yellow", 4);

	vector<Signal> signals;
	signals = 
	{
		{"\x1B[41m   \x1B[0m\n", redt},
		{"\x1B[43m   \x1B[0m\n", greent},
		{"\x1B[42m   \x1B[0m\n", yellowt},
	};

	TrafficLights trL(signals);
	trL.Start();
	return 0;
}
