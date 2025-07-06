#include "application.h"
#include "logger.h"

Application::Application(const ApplicationConfig& config):
m_config(config),
m_isRunning(true)
{
    if (m_initialized)
    {
        ARC_WARN("Application create more than once!")
    }
    m_initialized = true;
}

Application::~Application()
{
}

void Application::run()
{
    WindowGLFW window({
        m_config.name_,
        m_config.startWidth_,
        m_config.startHeight_,
        m_config.startPosX_,
        m_config.startPosY_
    });

    if (!window.init())
    {
        return;
    }

    ContextGLFW context(window.getWindow());

    if (!context.init())
    {
        return;
    }

    while (!window.shoudlWindowClose())
    {
        window.pollEvents();
        context.swapContext();
    }
}
