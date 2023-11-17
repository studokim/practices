#include <iostream>
#include <chrono>
#include <thread>
#include "./inih-master/cpp/INIReader.h"

class TrafficLight
{
private:
    int r_time, y_time, g_time;
    
    void cout_light(const std::string& color)
    {
        if(color == "red")
        std::cout << "\033[41m   \033[0m" << std::endl;
        
        else if(color == "yellow")
        std::cout << "\033[43m   \033[0m" << std::endl;
        
        else if(color == "green")
        std::cout << "\033[42m   \033[0m\r" << std::flush;
        
        else if(color == "empty")
        std::cout << "   \r" << std::flush;
        
        else
        {
            std::cout << "Unknown color: " << color << std::flush;
            exit(-1);
        }    
    }
public:
    TrafficLight()
    {
        r_time = 5;
        y_time = 5;
        g_time = 5;
        
    }
    
    TrafficLight(const std::string& path)
    {
        INIReader reader(path);
        
        if(reader.ParseError() == -2) 
        {
            std::cout << "Memory error\n";
            exit(-1);
        }
        else if(reader.ParseError() == -1) 
        {
            std::cout << "Can't load 'settings.ini'\n";
        }
        else if(reader.ParseError() > 0)
        {
            std::cout << "'settings.ini' has a syntax error\nIn line: " << reader.ParseError() << std::endl;
        }
        
        r_time = reader.GetInteger("timings", "red", -1);
        y_time = reader.GetInteger("timings", "yellow", -1);
        g_time = reader.GetInteger("timings", "green", -1);
        
        if(r_time < 0 || y_time < 0 || g_time < 0)
        {
            std::cout << "Invalid timing value\nStandard values will be applied (2 seconds)\n";
            system("sleep 4s");
            
            r_time = 3;
            y_time = 2;
            g_time = 2;
        }
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
            std::cout << std::endl << std::endl;
            
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
            std::cout << std::endl;
            
            cout_light("yellow");
            std::this_thread::sleep_for(std::chrono::seconds(y_time));
            
            std::cout << std::endl;
        }
    }
    
    
    
};

int main()
{
    
    TrafficLight traffic_light("../settings.ini");
    
    traffic_light.view_lights();
}
