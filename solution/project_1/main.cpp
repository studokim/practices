#include <iostream>
#include <thread>
#include <chrono>
#include "inih/cpp/INIReader.h"
using namespace std;


void displayColor(string& color, long timeSleepSecond)
{
	cout<<color<<'\n';
	this_thread::sleep_for(chrono::seconds(timeSleepSecond));		
}

void displayAnimateColor(string& color, long timeSleepSecond)
{
	cout<<color<<'\n';
	this_thread::sleep_for(chrono::seconds(timeSleepSecond));		
	for (size_t i = 0; i < 3; i++)	
	{
		system("clear");
		this_thread::sleep_for(chrono::milliseconds(600));	
		cout<<color<<endl;
		this_thread::sleep_for(chrono::milliseconds(600));	
	}	
}

class TrafficLight
{	
private:
	struct Signal
	{
		string color;
		long time_s;
		void (*displayColor)(string& color, long timeSleepSecond);
	};
	
	const int SIGNAL_SIZE = 5;
	Signal *signals;

public:
	TrafficLight(long redTime, long greenTime, long yellowTime)
	{		
		signals = new Signal[SIGNAL_SIZE] 
		{
			{"\x1B[41m   \x1B[0m\n", redTime, displayColor},
			{"\x1B[41m   \x1B[0m\n\x1B[43m   \x1B[0m\n", yellowTime, displayColor},
			{"\n\n\x1B[42m   \x1B[0m\n", greenTime, displayAnimateColor},
			{"\n\x1B[43m   \x1B[0m\n", yellowTime, displayColor},
			{"\x1B[41m   \x1B[0m\n", redTime, displayColor}
		};
	}

	void Start()
	{
		for(int i = 0; i<SIGNAL_SIZE; i++)
		{			
			system("clear");
			signals[i].displayColor(signals[i].color, signals[i].time_s);	
		}			
	}

	~TrafficLight() 
	{		
		delete[] signals;
	}
};


int main()
{
	
	INIReader reader("../timings.ini");
	if (reader.ParseError() < 0) 
	{
        std::cout << "Can't load 'timings.ini'\n";
        return 1;
    }

	long redt = reader.GetInteger("timings", "red", 4), 
	greent = reader.GetInteger("timings", "green", 1),
	yellowt = reader.GetInteger("timings", "yellow", 4);
	

	TrafficLight trL(redt, greent, yellowt);
	trL.Start();
	return 0;
}
