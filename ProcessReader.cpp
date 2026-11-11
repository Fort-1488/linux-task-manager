#include "ProcessReader.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

std::vector<ProcessInfo> ProcessReader::getAllProcesses()
{
    std::vector<ProcessInfo> processes;
    std::string procPath = "/proc";

    for(const auto& entry : fs::directory_iterator(procPath))
    {
        if(!entry.is_directory()) continue;

        std::string folderName = entry.path().filename().string();

        bool isPid = !folderName.empty() && std::all_of(folderName.begin(), folderName.end(), ::isdigit);
        if (!isPid) continue;

        ProcessInfo proc;
        proc.pid = std::stol(folderName);
        
        std::ifstream statusFile(entry.path() / "status");
        if (!statusFile.is_open()) continue;

        std::string line;
        while (std::getline(statusFile, line))
        {
            std::istringstream iss(line);
            std::string key;
            iss >> key;

            if(key == "Name:") {
                iss >> proc.name;
            } else if (key == "State:") {
                iss >> proc.state;
            } else if (key == "VmRSS:") {
                iss >> proc.memorykb;
            }
        }
        processes.push_back(proc);
    }
    return processes;
}
