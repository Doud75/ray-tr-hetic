#pragma once

#include "PerformanceTimer.hpp"
#include "MemoryMonitor.hpp"
#include <string>

/**
 * Collects and reports rendering performance metrics.
 * Tracks timing, memory, and statistics for raytracer execution.
 */
class RenderMetrics
{
private:
    PerformanceTimer totalRenderTimer;
    PerformanceTimer renderingLoopTimer;
    PerformanceTimer fileWriteTimer;

    unsigned int imageWidth;
    unsigned int imageHeight;
    size_t imageBufferSize;
    size_t peakMemoryUsage;
    size_t outputFileSize;

    bool renderStarted;
    bool renderCompleted;

    double CalculatePixelsPerSecond(
        double totalSeconds, unsigned int pixelCount) const;


    std::string FormatNumber(unsigned long long number) const;


    std::string FormatDouble(double value, int precision = 3) const;

public:
    RenderMetrics();
    ~RenderMetrics();

    void StartRender(unsigned int width, unsigned int height);

    void RecordImageBufferSize(size_t bufferSize);

    void StartRenderingLoop();

    void StopRenderingLoop();

    void StartFileWrite();

    void StopFileWrite();

    void RecordFileSize(size_t fileSize);

    void EndRender();

    std::string GenerateReport() const;

    double GetTotalRenderTimeMs() const;

    double GetPixelsPerSecond() const;
};


