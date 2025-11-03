#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

class Logger
{
public:
    enum class Level
    {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3
    };

private:
    Level currentLevel;
    bool enableTimestamp;
    
    std::string GetTimestamp() const;

    void LogMessage(Level level, const std::string& message) const;

public:
    Logger(Level level = Level::INFO, bool timestamp = true);
    ~Logger();

    void SetLevel(Level level);
    Level GetLevel() const;

    void Debug(const std::string& message) const;
    void Info(const std::string& message) const;
    void Warn(const std::string& message) const;
    void Error(const std::string& message) const;

    void ReportMetrics(const std::string& metricsReport) const;
};


