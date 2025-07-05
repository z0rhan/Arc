#include "logger.h"
#include "asserts.h"

bool initializeLogger()
{
    // TODO: Create log file
    return true;
}

void shutdownLogger()
{
    // TODO: Cleanup logging
}

ARC_API void reportAssertionFailure(const char *expression, const char *message, const char *file, int32_t line)
{
    if (*message == 0)
        logOutput(LogLevel::FATAL, "Assertion Failure: {}, in file: {}: {}", expression, file, line); 
    else
        logOutput(LogLevel::FATAL, "Assertion Failure: {}, Message: {}, in file: {}: {}", expression, message, file, line); 
}
