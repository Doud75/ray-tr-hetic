#pragma once

#include <cstddef>

/**
 * Memory monitoring utility for tracking memory usage.
 * Provides cross-platform memory tracking capabilities.
 * Falls back to estimation when system APIs are unavailable.
 */
class MemoryMonitor
{
public:
    /**
     * Gets current process memory usage in bytes.
     * Returns estimated value if system API unavailable.
     */
    static size_t GetCurrentMemoryUsage();

    /**
     * Gets peak memory usage in bytes during execution.
     * Returns estimated value if system API unavailable.
     */
    static size_t GetPeakMemoryUsage();

    /**
     * Converts bytes to megabytes for display.
     */
    static double BytesToMB(size_t bytes);

private:
    /**
     * Platform-specific implementation to get memory usage.
     */
    static size_t GetSystemMemoryUsage();

    /**
     * Estimates memory from known allocations.
     */
    static size_t EstimateMemoryUsage();
};


