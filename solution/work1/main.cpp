#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include "inih-master/cpp/INIReader.h"

enum class TrafficLightColor
{
    RED,
    YELLOW,
    GREEN
};

class TrafficLight
{
    long int redt;
    long int yellowt;
    long int greent;

    void displayColor(const TrafficLightColor &color)
    {
        switch (color)
        {
        case TrafficLightColor::RED:
            std::cout << "\x1B[41m R \x1B[0m" << std::endl;
            break;
        case TrafficLightColor::YELLOW:
            std::cout << "\x1B[103m Y \x1B[0m" << std::endl;
            break;
        case TrafficLightColor::GREEN:
            std::cout << "\x1B[42m G \x1B[0m" << std::flush;
            break;
        }
    }

public:
    TrafficLight()
    {
        INIReader reader("../timings.ini");
        if(reader.ParseError() == -2)
        {
            std::cout << "Memory error\n";
            exit(-2);
        }
        else if(reader.ParseError() == -1)
        {
            std::cout << "Can't load 'settings.ini'\n";
        }
        else if(reader.ParseError() > 0)
        {
            std::cout << "'settings.ini' has a syntax error\nIn line: " << reader.ParseError() << std::endl;
        }

        redt = reader.GetInteger("timings", "red", -1);
        yellowt = reader.GetInteger("timings", "yellow", -1);
        greent = reader.GetInteger("timings", "green", -1);

        if(redt < 0 || yellowt < 0 || greent < 0)
        {
            std::cout << "Invalid timing value\nStandard values will be applied (3 seconds)\n";
            system("sleep 4s");

            redt = 3;
            yellowt = 3;
            greent = 3;
        }
    }

    void view()
    {
        while (true)
        {
            system("clear");
            displayColor(TrafficLightColor::RED);
            std::this_thread::sleep_for(std::chrono::seconds(redt));
            displayColor(TrafficLightColor::YELLOW);
            std::this_thread::sleep_for(std::chrono::seconds(yellowt));
            system("clear");
            std::cout << std::endl;
            std::cout << std::endl;
            displayColor(TrafficLightColor::GREEN);
            std::this_thread::sleep_for(std::chrono::seconds(greent));

            for (int i = 0; i < 4; i++)
            {
                system("clear");
                std::cout << std::endl;
                std::cout << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                displayColor(TrafficLightColor::GREEN);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            system("clear");
            std::cout << std::endl;
            displayColor(TrafficLightColor::YELLOW);
            std::this_thread::sleep_for(std::chrono::seconds(yellowt));
        }
    }
};

int main()
{
    TrafficLight trafficLight;
    trafficLight.view();
    return 0;
}
