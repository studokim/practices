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
	displayColor(color, timeSleepSecond);
	for (int i = 0; i < 3; i++)	
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
		Signal(): showColor(displayColor) {}
		Signal(string color, long time, void (*displayColor)(string& color, long timeSleepSecond)):color(color), time_s(time), showColor(displayColor) {}
		string color{};
		long time_s{};
		void (*showColor)(string& color, long timeSleepSecond);
	};

	array<Signal, 4> signals;
	
public:
	TrafficLight(long redTime, long greenTime, long yellowTime)
	{
		signals = 
		{{
			Signal{"\x1B[41m   \x1B[0m\n", redTime, displayColor},
			Signal{"\x1B[41m   \x1B[0m\n\x1B[43m   \x1B[0m\n", yellowTime, displayColor},
			Signal{"\n\n\x1B[42m   \x1B[0m\n", greenTime, displayAnimateColor},
			Signal{"\n\x1B[43m   \x1B[0m\n", yellowTime, displayColor}
		}};
	}
	
	void Start()
	{
		while(true)
			for(int i = 0; i<signals.size(); i++)
			{				
				system("clear");
				signals[i].showColor(signals[i].color, signals[i].time_s);
			}
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
}
