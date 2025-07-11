#include "window_glfw.h"
#include "core/logger.h"
#include "event/glfwIntegration.h"
#include "event/event_dispatcher.h"
#include "event/event_key.h"

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

    // Set up event handling
    setupEventHandle();

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

void WindowGLFW::setupEventHandle()
{
    // Set up GLFW key event integration
    GLFWIntegration::setupKeyEvents(m_window);

    // Subscribe to key press events for window management
    EventDispatcher::subscribe<KeyPressedEvent>([this](const KeyPressedEvent& event) {
        if (event.getKeyCode() == GLFW_KEY_ESCAPE) {
            ARC_INFO("ESC key pressed - closing window");
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        }
        event.m_handled = TRUE;
    });

}

