#include <iostream>
#include <iomanip>
#include <algorithm>
#include "ProcessReader.hpp"
#include <thread>
#include <chrono>

int main() {
    while (true)
    {
        std::system("clear");

        ProcessReader reader;
        std::vector<ProcessInfo> list = reader.getAllProcesses();
        std::sort(list.begin(), list.end(), [](const ProcessInfo& a, const ProcessInfo& b){
            return a.memorykb > b.memorykb;
        }); 

        std::cout << "Найдено процессов: " << list.size() << "\n\n";

        std::cout << std::left << std::setw(8)  << "PID" 
                << std::left << std::setw(35) << "NAME" 
                << std::left << std::setw(15) << "MEMORY (Kb)" << "\n";
                
        std::cout << "---------------------------------------------------------\n";
        int printcout = 0;
        for (size_t i = 0; i < list.size(); ++i) {

            std::string displayName = list[i].name;

            if (list[i].memorykb > 6000) {

                if (displayName.length() > 32) {
                    displayName = displayName.substr(0, 29) + "...";
                }

                std::cout << std::left << std::setw(8)  << list[i].pid 
                        << std::left << std::setw(35) << displayName 
                        << std::left << std::setw(15) << list[i].memorykb << "\n";

                printcout++;
                if (printcout >= 15){
                    break;
                }
            }   
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } 
    return 0;
}
