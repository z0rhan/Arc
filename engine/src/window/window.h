#ifndef WINDOW_HH
#define WINDOW_HH

#include "defines.h"

class Window
{
public:
    virtual ~Window() = default;

    virtual bool init() = 0;
    virtual bool shoudlWindowClose() = 0;
    virtual void pollEvents() = 0;
};


#endif // WINDOW_HH
