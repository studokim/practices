#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "inih-master/ini.h"
#include "inih-master/ini.c"
#include "inih-master/cpp/INIReader.h"
#include "inih-master/cpp/INIReader.cpp"



class traffic_light{

    int8_t redt;
    int8_t yellowt;
    int8_t greent;

public:

    traffic_light()
    {
        INIReader reader("../timings.ini");
        if (reader.ParseError() < 0){
        redt=10;
        yellowt=3;
        greent=5;
        }
        else{
            redt= reader.GetInteger("timings","red",-1);
            yellowt= reader.GetInteger("timings","yellow",-1);
            greent=reader.GetInteger("timings","green",-1);
        }
    }

    void displayColor(const std::string& color) {
    if (color == "red") {
        std::cout << "\x1B[41m   \x1B[0m\n";
    }
    else if (color == "yellow") {
        std::cout << "\x1B[103m   \x1B[0m\n";
    }
    else if (color == "green") {
        std::cout << "\x1B[42m   \x1B[0m\n";
    }
    }

    void view() {

        while (true) {
        system("clear");
        displayColor("red");
        std::this_thread::sleep_for(std::chrono::seconds(redt));
        system("clear");
        displayColor("yellow");
        std::this_thread::sleep_for(std::chrono::seconds(yellowt));
        system("clear");
        displayColor("green");
        std::this_thread::sleep_for(std::chrono::seconds(greent));
        for(int i= 0;i<4;i++)
            {
            system("clear");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            displayColor("green");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
    }

};

int main() {
    traffic_light aboba;
    aboba.view();
}
