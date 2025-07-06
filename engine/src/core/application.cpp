#include "application.h"
#include "logger.h"
#include "factory.h"
#include "platform/platform.h"
#include "window/window_glfw.h"

// Static instance for singleton pattern
Application* Application::s_instance = nullptr;

Application::Application(const ApplicationConfig& config):
    m_config(config),
    m_isRunning(false)
{
    if (s_instance != nullptr)
    {
        ARC_WARN("Application created more than once! Previous instance will be overwritten.")
    }
    s_instance = this;
}

bool Application::initialize()
{
    if (m_initialized)
    {
        ARC_WARN("Application already initialized!")
        return true;
    }

    ARC_INFO("Initializing application: {}", m_config.name_)

    // Create window using factory
    WindowConfig windowConfig = {
        m_config.name_,
        m_config.startWidth_,
        m_config.startHeight_,
        m_config.startPosX_,
        m_config.startPosY_
    };

    m_window = EngineFactory::createWindow(windowConfig);
    if (!m_window)
    {
        ARC_ERROR("Failed to create window")
        return false;
    }

    if (!m_window->init())
    {
        ARC_ERROR("Failed to initialize window")
        return false;
    }

    // Create rendering context
    m_context = EngineFactory::createContext(m_window.get());
    if (!m_context)
    {
        ARC_ERROR("Failed to create rendering context")
        return false;
    }

    if (!m_context->init())
    {
        ARC_ERROR("Failed to initialize rendering context")
        return false;
    }

    // Call derived class initialization
    if (!onInitialize())
    {
        ARC_ERROR("Application-specific initialization failed")
        return false;
    }

    m_initialized = true;
    ARC_INFO("Application initialized successfully")
    return true;
}

void Application::run()
{
    if (!initialize())
    {
        ARC_FATAL("Failed to initialize application")
        return;
    }

    m_isRunning = true;
    ARC_INFO("Starting main loop")

    double lastTime = platformGetAbsoluteTime();

    while (m_isRunning && !m_window->shouldWindowClose())
    {
        // Calculate delta time
        double currentTime = platformGetAbsoluteTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        // Poll window events
        m_window->pollEvents();

        // Update application logic
        onUpdate(deltaTime);

        // Render frame
        onRender();

        // Swap buffers
        m_context->swapContext();
    }

    shutdown();
}

void Application::shutdown()
{
    if (!m_initialized)
    {
        return;
    }

    ARC_INFO("Shutting down application")

    // Call derived class cleanup
    onShutdown();

    // Clean up resources in reverse order of creation
    m_context.reset();
    m_window.reset();

    m_initialized = false;
    m_isRunning = false;

    if (s_instance == this)
    {
        s_instance = nullptr;
    }

    ARC_INFO("Application shutdown complete")
}
