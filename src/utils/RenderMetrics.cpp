#include "../../include/utils/RenderMetrics.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

RenderMetrics::RenderMetrics()
    : imageWidth(0), imageHeight(0), imageBufferSize(0),
      peakMemoryUsage(0), outputFileSize(0),
      totalPixelComputationTime(0.0),
      renderStarted(false), renderCompleted(false)
{
}

RenderMetrics::~RenderMetrics()
{
}

void RenderMetrics::StartRender(unsigned int width, unsigned int height)
{
    imageWidth = width;
    imageHeight = height;
    renderStarted = true;
    totalRenderTimer.Start();
    peakMemoryUsage = MemoryMonitor::GetCurrentMemoryUsage();
}

void RenderMetrics::RecordImageBufferSize(size_t bufferSize)
{
    imageBufferSize = bufferSize;
    size_t currentMemory = MemoryMonitor::GetCurrentMemoryUsage();
    if (currentMemory > peakMemoryUsage)
    {
        peakMemoryUsage = currentMemory;
    }
}

void RenderMetrics::StartRenderingLoop()
{
    renderingLoopTimer.Start();
}

void RenderMetrics::StopRenderingLoop()
{
    renderingLoopTimer.Stop();
    size_t currentMemory = MemoryMonitor::GetCurrentMemoryUsage();
    if (currentMemory > peakMemoryUsage)
    {
        peakMemoryUsage = currentMemory;
    }
}

void RenderMetrics::StartPixelComputation()
{
    pixelComputationTimer.Start();
}

void RenderMetrics::StopPixelComputation()
{
    pixelComputationTimer.Stop();
    double elapsed = pixelComputationTimer.GetElapsedMs();
    pixelComputationTimes.push_back(elapsed);
    totalPixelComputationTime += elapsed;
    pixelComputationTimer.Reset();
}

void RenderMetrics::StartFileWrite()
{
    fileWriteTimer.Start();
}

void RenderMetrics::StopFileWrite()
{
    fileWriteTimer.Stop();
}

void RenderMetrics::RecordFileSize(size_t fileSize)
{
    outputFileSize = fileSize;
}

void RenderMetrics::EndRender()
{
    totalRenderTimer.Stop();
    size_t currentMemory = MemoryMonitor::GetCurrentMemoryUsage();
    if (currentMemory > peakMemoryUsage)
    {
        peakMemoryUsage = currentMemory;
    }
    renderCompleted = true;
}

double RenderMetrics::CalculatePixelsPerSecond(
    double totalSeconds, unsigned int pixelCount) const
{
    if (totalSeconds <= 0.0 || pixelCount == 0)
    {
        return 0.0;
    }
    return static_cast<double>(pixelCount) / totalSeconds;
}

double RenderMetrics::CalculateAverageTimePerPixel(
    double totalSeconds, unsigned int pixelCount) const
{
    if (pixelCount == 0)
    {
        return 0.0;
    }
    double totalMicroseconds = totalSeconds * 1000000.0;
    return totalMicroseconds / static_cast<double>(pixelCount);
}

std::string RenderMetrics::FormatNumber(unsigned long long number) const
{
    std::stringstream ss;
    ss << std::fixed << number;
    std::string str = ss.str();
    
    int insertPos = str.length() - 3;
    while (insertPos > 0)
    {
        str.insert(insertPos, ",");
        insertPos -= 3;
    }
    return str;
}

std::string RenderMetrics::FormatDouble(double value, int precision) const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    return ss.str();
}

std::string RenderMetrics::GenerateReport() const
{
    if (!renderCompleted)
    {
        return "Metrics report unavailable: Render not completed.";
    }

    unsigned int totalPixels = imageWidth * imageHeight;
    double totalRenderMs = GetTotalRenderTimeMs();
    double totalRenderSec = totalRenderMs / 1000.0;
    double pixelsPerSec = GetPixelsPerSecond();
    double avgTimePerPixel = GetAverageTimePerPixelUs();
    double loopTimeMs = renderingLoopTimer.GetElapsedMs();
    double fileWriteMs = fileWriteTimer.GetElapsedMs();

    std::stringstream report;
    
    report << "=== Raytracer Performance Metrics ===" << std::endl;
    report << "Image Dimensions: " << imageWidth << "x" << imageHeight;
    report << " (" << FormatNumber(totalPixels) << " pixels)" << std::endl;
    report << "----------------------------------------" << std::endl;
    report << "Timing:" << std::endl;
    report << "  Total Render Time:       " 
           << std::setw(10) << FormatDouble(totalRenderMs) << " ms" << std::endl;
    report << "  Rendering Loop Time:     " 
           << std::setw(10) << FormatDouble(loopTimeMs) << " ms" << std::endl;
    report << "  Pixel Computation:       " 
           << std::setw(10) << FormatDouble(totalPixelComputationTime) << " ms" << std::endl;
    report << "  File Write Time:         " 
           << std::setw(10) << FormatDouble(fileWriteMs) << " ms" << std::endl;
    report << "----------------------------------------" << std::endl;
    report << "Performance:" << std::endl;
    report << "  Pixels per Second:       " 
           << std::setw(10) << FormatNumber(static_cast<unsigned long long>(pixelsPerSec)) 
           << " pps" << std::endl;
    report << "  Average Time per Pixel:  " 
           << std::setw(10) << FormatDouble(avgTimePerPixel, 3) << " μs" << std::endl;
    report << "----------------------------------------" << std::endl;
    report << "Memory:" << std::endl;
    report << "  Image Buffer Size:       " 
           << std::setw(10) << FormatDouble(MemoryMonitor::BytesToMB(imageBufferSize), 2) 
           << " MB" << std::endl;
    report << "  Peak Memory Usage:       " 
           << std::setw(10) << FormatDouble(MemoryMonitor::BytesToMB(peakMemoryUsage), 2) 
           << " MB" << std::endl;
    report << "----------------------------------------" << std::endl;
    report << "File:" << std::endl;
    report << "  Output File Size:        " 
           << std::setw(10) << FormatDouble(outputFileSize / 1024.0, 2) 
           << " KB" << std::endl;
    report << "========================================";

    return report.str();
}

double RenderMetrics::GetTotalRenderTimeMs() const
{
    return totalRenderTimer.GetElapsedMs();
}

double RenderMetrics::GetPixelsPerSecond() const
{
    unsigned int totalPixels = imageWidth * imageHeight;
    double totalSeconds = GetTotalRenderTimeMs() / 1000.0;
    return CalculatePixelsPerSecond(totalSeconds, totalPixels);
}

double RenderMetrics::GetAverageTimePerPixelUs() const
{
    unsigned int totalPixels = imageWidth * imageHeight;
    double totalSeconds = totalPixelComputationTime / 1000.0;
    return CalculateAverageTimePerPixel(totalSeconds, totalPixels);
}


