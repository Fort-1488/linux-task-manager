#pragma once

#include <string>

struct ProcessInfo
{
    int pid = 0;
    std::string name;
    std::string state;
    size_t memorykb = 0; 
};

