#pragma once

#include <chrono>
#include <string>

class PerformanceTimer
{
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point stopTime;
    bool isRunning;
    bool hasStopped;

public:
    PerformanceTimer();
    ~PerformanceTimer();

    void Start();

    void Stop();

    void Reset();

    double GetElapsedMs() const;

    double GetElapsedSeconds() const;

    bool IsRunning() const;

    bool HasStopped() const;
};


