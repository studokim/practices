#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include "inih-master/cpp/INIReader.h"

class TrafficLight
{
    long int redt;
    long int yellowt;
    long int greent;

    void displayColor(const std::string &color)
    {
        if (color == "red")
        {
            std::cout << "\x1B[41m R \x1B[0m" << std::endl;
        }
        else if (color == "yellow")
        {
            std::cout << "\x1B[103m Y \x1B[0m" << std::endl;
        }
        else if (color == "green")
        {
            std::cout << "\x1B[42m G \x1B[0m" << std::flush;
        }
        else
        {
            std::cout << "Ошибка отображения цвета" << std::endl;
            exit(1);
        }
    }

public:
    TrafficLight()
    {
        INIReader reader("../timings.ini");
        if (reader.ParseError() < 0)
        {
            std::cout << "Ошибка прогрузки ini-файла" << std::endl;
            exit(1);
        }
        else
        {
            redt = reader.GetInteger("timings", "red", 5);
            yellowt = reader.GetInteger("timings", "yellow", 3);
            greent = reader.GetInteger("timings", "green", 5);
        }
    }

    void view()
    {
        while (true)
        {
            system("clear");
            displayColor("red");
            std::this_thread::sleep_for(std::chrono::seconds(redt));
            displayColor("yellow");
            std::this_thread::sleep_for(std::chrono::seconds(yellowt));
            system("clear");
            std::cout << std::endl;
            std::cout << std::endl;
            displayColor("green");
            std::this_thread::sleep_for(std::chrono::seconds(greent));
            for (int i = 0; i < 4; i++)
            {
                system("clear");
                std::cout << std::endl;
                std::cout << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                displayColor("green");
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            system("clear");
            std::cout << std::endl;
            displayColor("yellow");
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
