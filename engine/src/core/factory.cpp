#include "factory.h"
#include "core/logger.h"

// Forward declare to avoid header conflicts
class WindowGLFW;
class ContextGLFW;

#include "window/window_glfw.h"
#include "renderer/GL_context_glfw.h"

std::unique_ptr<Window> EngineFactory::createWindow(const WindowConfig& config)
{
    // For now, we only support GLFW, but this can be extended
    // to support other windowing systems (SDL, Win32, etc.)
    try 
    {
        return std::make_unique<WindowGLFW>(config);
    }
    catch (const std::exception& e)
    {
        ARC_ERROR("Failed to create window: {}", e.what())
        return nullptr;
    }
}

std::unique_ptr<Context> EngineFactory::createContext(Window* window)
{
    if (!window)
    {
        ARC_ERROR("Cannot create context: window is null")
        return nullptr;
    }

    // Cast to GLFW window to get the native handle
    WindowGLFW* glfwWindow = dynamic_cast<WindowGLFW*>(window);
    if (!glfwWindow)
    {
        ARC_ERROR("Window is not a GLFW window")
        return nullptr;
    }

    try 
    {
        return std::make_unique<ContextGLFW>(glfwWindow->getWindow());
    }
    catch (const std::exception& e)
    {
        ARC_ERROR("Failed to create rendering context: {}", e.what())
        return nullptr;
    }
}
