#include "window_glfw.h"
#include "core/logger.h"

#include <GLFW/glfw3.h>

WindowGLFW::WindowGLFW(const WindowConfig& config):
    m_window(nullptr),
    m_config(config)
{
}

WindowGLFW::~WindowGLFW()
{
}

bool WindowGLFW::init()
{
    glfwSetErrorCallback(GLFWErrorCallBack);
    if (!glfwInit())
    {
        ARC_FATAL("Failed to initialize GLFW!")
        return FALSE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_config.width_,
                                m_config.height_,
                                m_config.name_.c_str(),
                                nullptr,
                                nullptr);

    if (!m_window)
    {
        ARC_FATAL("Failed to create window!");
        return FALSE;
    }

    // Wayland does not support window positioning
    // glfwSetWindowPos(m_window, m_config.startPosX_, m_config.startPosY_);

    return TRUE;
}

bool WindowGLFW::shouldWindowClose()
{
    return glfwWindowShouldClose(m_window);
}

void WindowGLFW::pollEvents()
{
    glfwPollEvents();
}

void WindowGLFW::GLFWErrorCallBack(int32_t error, const char* desc)
{
    ARC_ERROR("GLFW Error: {} : {}", error, desc);
}

