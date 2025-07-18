#include "application.h"
#include "logger.h"
#include "asserts.h"
#include "factory.h"
#include "platform/platform.h"

// Static instance for singleton pattern
Application* Application::s_instance = nullptr;

Application::Application(const ApplicationConfig& config):
    m_config(config),
    m_isRunning(false)
{
    ARC_ASSERT_MSG(s_instance == nullptr, "Application already exists!!!")
    s_instance = this;
}

Application& Application::getInstance()
{
    ARC_ASSERT_MSG(s_instance != nullptr, "Application instance not created!!!")
    return *s_instance;
}

bool Application::initialize()
{
    if (!isConfigValid())
    {
        ARC_FATAL("Invalid application configuration.");
        return false;
    }

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
    if (s_instance == this)
    {
        s_instance = nullptr;
    }

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

    ARC_INFO("Application shutdown complete")
}

bool Application::isConfigValid() const
{
    if (m_config.name_ == nullptr || m_config.name_[0] == '\0')
    {
        ARC_ERROR("Config validation failed: name is null or empty");
        return false;
    }

    if (m_config.startWidth_ <= 0 || m_config.startHeight_ <= 0)
    {
        ARC_ERROR("Config validation failed: invalid window dimensions");
        return false;
    }

    if (m_config.startPosX_ < 0 || m_config.startPosY_ < 0)
    {
        ARC_ERROR("Config validation failed: invalid window position");
        return false;
    }

    return true;
}
