#include <cstdint> // For fixed sized accross platforms

#define TRUE 1
#define FALSE 0

// For MSVC
//#if defined(_WIN32) || defined(_WIN64)
//    #ifdef MYLIBRARY_EXPORTS
//        #define ARC_API __declspec(dllexport)
//    #else
//        #define ARC_API __declspec(dllimport)
//    #endif
//#else
//    #define ARC_API
//#endif

// Windows .dll specific
#ifdef ARC_EXPORT
#ifdef _MSC_VER
#define ARC_API __declspec(dllexport)
#else
#define ARC_API __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define ARC_API __declspec(dllimport)
#else
#define ARC_API
#endif
#endif

// Platforms
//
// Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define ARC_PLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on windows"
#endif
// Linux
#elif defined(__linux__) || defined(__gnu_linux__)
#define ARC_PLATFORM_LINUX 1
// Ohter platforms not supported for now
#else
#error "Unsupported platform"
#endif
