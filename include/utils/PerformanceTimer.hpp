#pragma once

#include <chrono>
#include <string>

/**
 * High-resolution performance timer for measuring execution time.
 * Uses std::chrono::high_resolution_clock for maximum precision.
 * Supports start/stop/reset operations and RAII scoped timing.
 */
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

    /**
     * Starts the timer.
     */
    void Start();

    /**
     * Stops the timer.
     */
    void Stop();

    /**
     * Resets the timer to initial state.
     */
    void Reset();

    /**
     * Gets elapsed time in milliseconds.
     */
    double GetElapsedMs() const;

    /**
     * Gets elapsed time in seconds.
     */
    double GetElapsedSeconds() const;

    /**
     * Checks if timer is currently running.
     */
    bool IsRunning() const;

    /**
     * Checks if timer has been stopped.
     */
    bool HasStopped() const;
};


