#include "platform.h"

// Linux platform layer
#if ARC_PLATFORM_LINUX

#include "core/logger.h"

#include <cstring>
#include <iostream>
#include <new> // ::operator new

#if _POSIX_C_SOURCE >= 199309L
#include <time.h> // nanosleep
#else
#include <unistd.h>
#endif

constexpr const char* ANSI_COLORS[] = {
    "\033[0;41m",  // FATAL - Red background
    "\033[1;31m",  // ERROR - Bright red
    "\033[1;33m",  // WARN  - Bright yellow
    "\033[1;32m",  // INFO  - Bright green
    "\033[1;34m",  // DEBUG - Bright blue
    "\033[1;30m"   // TRACE - Bright black (gray)
};
constexpr const char* ANSI_RESET = "\033[0m\n";

// Memory allocation
void* platformAlloc(uint64_t size, bool aligned)
{
    // TODO: memory alignment
    return ::operator new(size);
}
void platformFree(void* block, bool aligned)
{
    // TODO: memory alignment
    ::operator delete(block);
}

void* platformSetMemory(void* block, int32_t value, uint64_t size)
{
    return std::memset(block, value, static_cast<size_t>(size));
}

void* platformZeroMemory(void* block, uint64_t size)
{
    return platformSetMemory(block, 0, size);
}

void* platformCopyMemory(void* dest, const void* source, uint64_t size){
    return std::memcpy(dest, source, static_cast<size_t>(size));
}

// Write to console
void platformConsoleWrite(const char* msg, uint8_t color)
{
    if (color < 6)
    {
        std::cout << ANSI_COLORS[color] << msg << ANSI_RESET;
    }
    else
    {
        std::cout << msg;
    }
    // Doesn't work with std::format for some reason
    //std::cout << std::format("\330[{}m{}\033[0m\n", colorStrings[color], msg);
}

void platformConsoleWriteError(const char* msg, uint8_t color)
{
    if (color < 6)
    {
        std::cout << ANSI_COLORS[color] << msg << ANSI_RESET;
    }
    else
    {
        std::cout << msg;
    }
}

double platformGetAbsoluteTime()
{
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    
    return now.tv_sec + now.tv_nsec * 0.000000001;
}

void platformSleep(uint64_t ms)
{
#if _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000 * 1000;
    nanosleep(&ts, 0);
#else
    if (ms > 1000)
    {
        sleep(ms / 1000);
    }
    usleep((ms % 1000) * 1000);
#endif
}


#endif // ARC_PLATFORM_LINUX
