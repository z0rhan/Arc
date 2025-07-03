#if defined(_WIN32) || defined(_WIN64)
    #ifdef MYLIBRARY_EXPORTS
        #define ARC_API __declspec(dllexport)
    #else
        #define ARC_API __declspec(dllimport)
    #endif
#else
    #define ARC_API
#endif
