#include "MemoryMonitor.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>

#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
    #include <sys/resource.h>
#endif

size_t MemoryMonitor::GetCurrentMemoryUsage()
{
    size_t systemMemory = GetSystemMemoryUsage();
    
    if (systemMemory > 0)
    {
        return systemMemory;
    }
    
    return EstimateMemoryUsage();
}

size_t MemoryMonitor::GetPeakMemoryUsage()
{
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), 
        (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        return static_cast<size_t>(pmc.PeakWorkingSetSize);
    }
#elif defined(__linux__)
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0)
    {
        return static_cast<size_t>(usage.ru_maxrss * 1024);
    }
#elif defined(__APPLE__)
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0)
    {
        return static_cast<size_t>(usage.ru_maxrss);
    }
#endif
    
    return EstimateMemoryUsage();
}

double MemoryMonitor::BytesToMB(size_t bytes)
{
    return static_cast<double>(bytes) / (1024.0 * 1024.0);
}

size_t MemoryMonitor::GetSystemMemoryUsage()
{
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), 
        (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        return static_cast<size_t>(pmc.WorkingSetSize);
    }
#elif defined(__linux__)
    FILE* file = fopen("/proc/self/status", "r");
    if (file != nullptr)
    {
        char line[128];
        while (fgets(line, sizeof(line), file) != nullptr)
        {
            if (strncmp(line, "VmRSS:", 6) == 0)
            {
                size_t memKB = 0;
                sscanf(line, "VmRSS: %zu", &memKB);
                fclose(file);
                return memKB * 1024;
            }
        }
        fclose(file);
    }
#elif defined(__APPLE__)
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0)
    {
        return static_cast<size_t>(usage.ru_maxrss);
    }
#endif
    
    return 0;
}

size_t MemoryMonitor::EstimateMemoryUsage()
{
    return 0;
}

