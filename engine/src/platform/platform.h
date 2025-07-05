#ifndef PLATFORM_HH
#define PLATFORM_HH

#include "defines.h"

// Memory allocation
void* platformAlloc(uint64_t size, bool aligned);
void platformFree(void* block, bool aligned);
void* platformZeroMemory(void* block, uint64_t size);
void* platformCopyMemory(void* dest, const void* source, uint64_t size);
void* platformSetMemory(void* block, int32_t value, uint64_t size);

// Color our console msg
void platformConsoleWrite(const char* msg, uint8_t color);
void platformConsoleWriteError(const char* msg, uint8_t color);

double platformGetAbsoluteTime();

void platformSleep(uint64_t ms);

#endif // PLATFORM_HH
