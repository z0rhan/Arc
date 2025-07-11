#ifndef WINDOW_HH
#define WINDOW_HH

#include "defines.h"

#include <string>

struct WindowConfig
{
    std::string name_;

    int32_t width_;
    int32_t height_;
    int32_t startPosX_;
    int32_t startPosY_;
};


class Window
{
public:
    virtual ~Window() = default;

    virtual bool init() = 0;
    virtual bool shouldWindowClose() = 0;
    virtual void pollEvents() = 0;

    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;
};

#endif // WINDOW_HH
