#include "platform.h"

// Linux platform layer
#if ARC_PLATFORM_LINUX

#include "core/logger.h"

#include <cstring>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h> // nanosleep
#endif

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

void platformConsoleWrite(const char* msg, uint8_t color)
{
    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    const char* colorStrings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    std::cout << "\033[" << colorStrings[color] << "m" << msg << "\033[0m";
    // Doesn't work with std::format for some reason
    //std::cout << std::format("\330[{}m{}\033[0m\n", colorStrings[color], msg);
}

void platformConsoleWriteError(const char* msg, uint8_t color)
{
    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    const char* colorStrings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    std::cout << "\033[" << colorStrings[color] << "m" << msg << "\033[0m";
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
    unsleep((ms % 1000) * 1000);
#endif
}


#endif
