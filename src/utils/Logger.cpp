#include "../../include/utils/Logger.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>

Logger::Logger(Level level, bool timestamp)
    : currentLevel(level), enableTimestamp(timestamp)
{
}

Logger::~Logger()
{
}

void Logger::SetLevel(Level level)
{
    currentLevel = level;
}

Logger::Level Logger::GetLevel() const
{
    return currentLevel;
}

std::string Logger::GetTimestamp() const
{
    if (!enableTimestamp)
    {
        return "";
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::tm* tm_ptr;
#ifdef _WIN32
    std::tm tm_buf;
    localtime_s(&tm_buf, &time);
    tm_ptr = &tm_buf;
#else
    std::tm tm_buf;
    localtime_r(&time, &tm_buf);
    tm_ptr = &tm_buf;
#endif
    
    std::stringstream ss;
    ss << std::put_time(tm_ptr, "%H:%M:%S");
    
    return "[" + ss.str() + "] ";
}

void Logger::LogMessage(Level level, const std::string& message) const
{
    if (level < currentLevel)
    {
        return;
    }

    std::string prefix;
    switch (level)
    {
        case Level::DEBUG:
            prefix = "[DEBUG] ";
            break;
        case Level::INFO:
            prefix = "[INFO]  ";
            break;
        case Level::WARN:
            prefix = "[WARN]  ";
            break;
        case Level::ERROR:
            prefix = "[ERROR] ";
            break;
    }

    std::cout << GetTimestamp() << prefix << message << std::endl;
}

void Logger::Debug(const std::string& message) const
{
    LogMessage(Level::DEBUG, message);
}

void Logger::Info(const std::string& message) const
{
    LogMessage(Level::INFO, message);
}

void Logger::Warn(const std::string& message) const
{
    LogMessage(Level::WARN, message);
}

void Logger::Error(const std::string& message) const
{
    LogMessage(Level::ERROR, message);
}

void Logger::ReportMetrics(const std::string& metricsReport) const
{
    std::cout << std::endl << metricsReport << std::endl;
}

