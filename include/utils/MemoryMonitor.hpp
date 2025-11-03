#pragma once

#include <cstddef>

class MemoryMonitor
{
public:
    static size_t GetCurrentMemoryUsage();

    static size_t GetPeakMemoryUsage();

    static double BytesToMB(size_t bytes);

private:
    static size_t GetSystemMemoryUsage();

    static size_t EstimateMemoryUsage();
};


