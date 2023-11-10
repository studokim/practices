#include <iostream>
#include <chrono>
#include <thread>
#include "./inih-master/ini.h"
#include "./inih-master/ini.c"
#include "./inih-master/cpp/INIReader.h"
#include "./inih-master/cpp/INIReader.cpp"




class traffic_light
{
private:
    int g_time, y_time, r_time;
public:
    traffic_light()
    {
        color_time(5, 5, 5);
    }
    

    traffic_light(int g_time, int y_time, int r_time)
    {
        color_time(g_time, y_time, r_time);
    }
    
    traffic_light(const std::string& path)
    {
        INIReader reader(path);
        
        if (reader.ParseError() < 0) {
            std::cout << "Error\n";
            exit(-1);
        }
        
        color_time(reader.GetInteger("color", "green", 2),
                   reader.GetInteger("color", "yellow", 2),
                   reader.GetInteger("color", "red", 2));
    }
    
    void color_time(int g_time, int y_time, int r_time)
    {
        this->g_time = g_time;
        this->y_time = y_time;
        this->r_time = r_time;
    }
    
    void work()
    {
        while (true)
        {   
            system("clear");
            std::cout << "\033[42;m    \n    \033[0m" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(g_time));
            
            for (int i = 0; i < 5; i++)
            {
                system("clear");
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                std::cout << "\033[42m    \n    \033[0m" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(250));

            }
            
            system("clear");
            std::cout << "\033[43m    \n    \033[0m" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(y_time));
            
            system("clear");
            std::cout << "\033[41m    \n    \033[0m" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(r_time));
        }
    }
};

int main()
{
    
    traffic_light A("../path.ini");
    //traffic_light A(2, 20, 1);
    
    A.work();
    
    return 0;
}
