#pragma once

#include "PerformanceTimer.hpp"
#include "MemoryMonitor.hpp"
#include <string>
#include <vector>

/**
 * Collects and reports rendering performance metrics.
 * Tracks timing, memory, and statistics for raytracer execution.
 */
class RenderMetrics
{
private:
    PerformanceTimer totalRenderTimer;
    PerformanceTimer renderingLoopTimer;
    PerformanceTimer pixelComputationTimer;
    PerformanceTimer fileWriteTimer;

    unsigned int imageWidth;
    unsigned int imageHeight;
    size_t imageBufferSize;
    size_t peakMemoryUsage;
    size_t outputFileSize;

    std::vector<double> pixelComputationTimes;
    double totalPixelComputationTime;

    bool renderStarted;
    bool renderCompleted;

    /**
     * Calculates pixels per second from total time and pixel count.
     */
    double CalculatePixelsPerSecond(
        double totalSeconds, unsigned int pixelCount) const;

    /**
     * Calculates average time per pixel in microseconds.
     */
    double CalculateAverageTimePerPixel(
        double totalSeconds, unsigned int pixelCount) const;

    /**
     * Formats a number with thousands separators.
     */
    std::string FormatNumber(unsigned long long number) const;

    /**
     * Formats a double value with specified precision.
     */
    std::string FormatDouble(double value, int precision = 3) const;

public:
    RenderMetrics();
    ~RenderMetrics();

    /**
     * Starts the total render timer and initializes metrics.
     */
    void StartRender(unsigned int width, unsigned int height);

    /**
     * Records image buffer size after allocation.
     */
    void RecordImageBufferSize(size_t bufferSize);

    /**
     * Starts timing the rendering loop.
     */
    void StartRenderingLoop();

    /**
     * Stops timing the rendering loop.
     */
    void StopRenderingLoop();

    /**
     * Starts timing pixel computation (per pixel or batch).
     */
    void StartPixelComputation();

    /**
     * Stops timing pixel computation and accumulates time.
     */
    void StopPixelComputation();

    /**
     * Starts timing file write operation.
     */
    void StartFileWrite();

    /**
     * Stops timing file write operation.
     */
    void StopFileWrite();

    /**
     * Records the output file size.
     */
    void RecordFileSize(size_t fileSize);

    /**
     * Completes render metrics collection.
     */
    void EndRender();

    /**
     * Generates formatted metrics report string.
     */
    std::string GenerateReport() const;

    /**
     * Gets total render time in milliseconds.
     */
    double GetTotalRenderTimeMs() const;

    /**
     * Gets pixels per second throughput.
     */
    double GetPixelsPerSecond() const;

    /**
     * Gets average time per pixel in microseconds.
     */
    double GetAverageTimePerPixelUs() const;
};


