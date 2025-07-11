#ifndef LOGGER_HH
#define LOGGER_HH

#include "defines.h"
#include "platform/platform.h"
#include <format>
#include <iostream>
#include <string>
#include <string_view>

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace for release
#if RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

bool initializeLogger();
void shutdownLogger();

enum class LogLevel : int
{
    FATAL = 0,
    ERROR = 1,
    WARN = 2,
    INFO = 3,
    DEBUG = 4,
    TRACE = 5
};

constexpr std::string_view logLevelStrings[6] = {
    "[FATAL]: ",
    "[ERROR]: ",
    "[WARN]: ",
    "[INFO]: ",
    "[DEBUG]: ",
    "[TRACE]: "
};

template <typename... Args>
void logOutput(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
{
    bool isError = static_cast<int>(level) <= static_cast<int>(LogLevel::ERROR);

    std::string message = std::format(fmt, std::forward<Args>(args)...);
    std::string_view prefix = logLevelStrings[static_cast<int>(level)];

    std::string fullMsg = std::format("{}{}\n", prefix, message);

    // Platform Specific output - Fixed logic
    if (isError)
        platformConsoleWriteError(fullMsg.c_str(), static_cast<uint8_t>(level));
    else
        platformConsoleWrite(fullMsg.c_str(), static_cast<uint8_t>(level));
}

// Log Fatal messages
#define ARC_FATAL(message, ...) logOutput(LogLevel::FATAL, message __VA_OPT__(,) __VA_ARGS__);

// Log Error messages
#ifndef ARC_ERROR
#define ARC_ERROR(message, ...) logOutput(LogLevel::ERROR, message __VA_OPT__(,) __VA_ARGS__);
#endif

// Log Warn messages if enabled
#if LOG_WARN_ENABLED == 1
#define ARC_WARN(message, ...) logOutput(LogLevel::WARN, message __VA_OPT__(,) __VA_ARGS__);
#else
#define ARC_WARN(message, ...)
#endif

// Log Info messages if enabled
#if LOG_INFO_ENABLED == 1
#define ARC_INFO(message, ...) logOutput(LogLevel::INFO, message __VA_OPT__(,) __VA_ARGS__);
#else
#define ARC_INFO(message, ...)
#endif

// Log Debug messages if enabled
#if LOG_DEBUG_ENABLED == 1
#define ARC_DEBUG(message, ...) logOutput(LogLevel::DEBUG, message __VA_OPT__(,) __VA_ARGS__);
#else
#define ARC_DEBUG(message, ...)
#endif

// Log Trace messages if enabled
#if LOG_TRACE_ENABLED == 1
#define ARC_TRACE(message, ...) logOutput(LogLevel::TRACE, message __VA_OPT__(,) __VA_ARGS__);
#else
#define ARC_TRACE(message, ...)
#endif

#endif // LOGGER_HH
