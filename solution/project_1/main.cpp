#include <iostream>
#include <chrono>
#include <thread>
#include "./inih-master/cpp/INIReader.h"

class TrafficLights
{
private:
    int r_time, y_time, g_time;
public:
    TrafficLights()
    {
        r_time = 5;
        y_time = 5;
        g_time = 5;
        
    }
    
    TrafficLights(const std::string& path)
    {
        INIReader reader(path);
        
        if (reader.ParseError() < 0) {
            std::cout << "Can't load 'settings.ini'\n";
            exit(-1);
        }
        
        r_time = reader.GetInteger("timings", "red", 2);
        y_time = reader.GetInteger("timings", "yellow", 2);
        g_time = reader.GetInteger("timings", "green", 2);
    }
    
    void cout_light(const std::string& color)
    {
        if(color == "red")
        std::cout << "\033[41m   \033[0m" << std::endl;
        
        if(color == "yellow")
        std::cout << "\033[43m   \033[0m" << std::endl;
        
        if(color == "green")
        std::cout << "\033[42m   \033[0m\r" << std::flush;
        
        if(color == "empty")
        std::cout << "\033[45m   \033[0m\r" << std::flush;
            
    }
    
    void view_lights()
    {
        while (true)
        {   
            system("clear");
            cout_light("red");
            std::this_thread::sleep_for(std::chrono::seconds(r_time));
            
            
            cout_light("yellow");
            std::this_thread::sleep_for(std::chrono::seconds(y_time));
            
            system("clear");
            
            cout_light("green");
            std::this_thread::sleep_for(std::chrono::seconds(g_time));
            
            for (int i = 0; i < 5; i++)
            {
                cout_light("empty");
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                cout_light("green");
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
            }
            
            system("clear");
            
            cout_light("yellow");
            std::this_thread::sleep_for(std::chrono::seconds(y_time));
            
            
            std::cout << std::endl;
        }
    }
};

int main()
{
    
    TrafficLights traffic_light("../settings.ini");
    
    traffic_light.view_lights();
    
    return 0;
}
