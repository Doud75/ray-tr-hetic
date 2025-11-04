#include "PerformanceTimer.hpp"

PerformanceTimer::PerformanceTimer()
    : isRunning(false), hasStopped(false)
{
}

PerformanceTimer::~PerformanceTimer()
{
}

void PerformanceTimer::Start()
{
    startTime = std::chrono::high_resolution_clock::now();
    isRunning = true;
    hasStopped = false;
}

void PerformanceTimer::Stop()
{
    if (isRunning)
    {
        stopTime = std::chrono::high_resolution_clock::now();
        isRunning = false;
        hasStopped = true;
    }
}

void PerformanceTimer::Reset()
{
    isRunning = false;
    hasStopped = false;
}

double PerformanceTimer::GetElapsedMs() const
{
    if (!hasStopped && !isRunning)
    {
        return 0.0;
    }

    auto endTime = isRunning 
        ? std::chrono::high_resolution_clock::now()
        : stopTime;

    auto duration = std::chrono::duration_cast<
        std::chrono::microseconds>(endTime - startTime);
    
    return duration.count() / 1000.0;
}

double PerformanceTimer::GetElapsedSeconds() const
{
    return GetElapsedMs() / 1000.0;
}

bool PerformanceTimer::IsRunning() const
{
    return isRunning;
}

bool PerformanceTimer::HasStopped() const
{
    return hasStopped;
}


