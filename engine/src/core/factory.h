#ifndef FACTORY_H
#define FACTORY_H

#include "window/window.h"
#include "renderer/GL_context.h"
#include <memory>

struct WindowConfig;

class EngineFactory 
{
public:
    static std::unique_ptr<Window> createWindow(const WindowConfig& config);
    static std::unique_ptr<Context> createContext(Window* window);
};

#endif // FACTORY_H
