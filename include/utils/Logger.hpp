#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

/**
 * Logger class for standardized logging with levels.
 * Supports INFO, DEBUG, WARN, and ERROR log levels.
 * Provides timestamp formatting and configurable output.
 */
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
    
    /**
     * Gets current timestamp as formatted string.
     */
    std::string GetTimestamp() const;

    /**
     * Formats log message with level prefix.
     */
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

    /**
     * Logs a formatted metrics report.
     */
    void ReportMetrics(const std::string& metricsReport) const;
};


