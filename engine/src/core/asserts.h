#ifndef ASSERTS_HH
#define ASSERTS_HH

#include "defines.h"

// Disabel assertions by commenting the line below
#define ARC_ASSERTIONS_ENABLED

// If assertions is enabled
#ifdef ARC_ASSERTIONS_ENABLED

// Platform-specific break
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __bebugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

ARC_API void reportAssertionFailure(const char *expression, const char *message, const char *file, int32_t line);

// General assert
#define ARC_ASSERT(expr)                                                                           \
    {                                                                                              \
        if (expr)                                                                                  \
        {                                                                                          \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            reportAssertionFailure(#expr, "", __FILE__, __LINE__);                                 \
            debugBreak();                                                                          \
        }                                                                                          \
    }

// Assert with message
#define ARC_ASSERT_MSG(expr, message)                                                              \
    {                                                                                              \
        if (expr)                                                                                  \
        {                                                                                          \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            reportAssertionFailure(#expr, message, __FILE__, __LINE__);                            \
            debugBreak();                                                                          \
        }                                                                                          \
    }

// Debug-only assert
#ifdef _DEBUG
#define ARC_ASSERT_DEBUG(expr) ARC_ASSERT(expr)
#else
#define ARC_ASSERT_DEBUG(expr)
#endif

// If assertions is disabled
#else
#define ARC_ASSERT(expr)
#define ARC_ASSERT_MSG(expr, message)
#define ARC_ASSERT_DEBUG(expr)
#endif

#endif // ASSERTS_HH
