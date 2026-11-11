#pragma once

#include <vector>
#include "ProcessInfo.hpp"

class ProcessReader 
{
    public:
        std::vector<ProcessInfo> getAllProcesses();
};