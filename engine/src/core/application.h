#ifndef APPLICATION_HH
#define APPLICATION_HH

#include "defines.h"
#include "window/window.h"
#include "renderer/GL_context.h"
#include <memory>

struct ApplicationConfig
{
    const char* name_;        // Use const char* for string literals
    int32_t     startWidth_;
    int32_t     startHeight_;
    int32_t     startPosX_;
    int32_t     startPosY_;
};

class Application
{
public:
    explicit Application(const ApplicationConfig& config);
    virtual ~Application() = default;

    bool initialize();
    void run();
    void shutdown();

protected:
    // Allow derived applications to override behavior
    virtual bool onInitialize() = 0;
    virtual void onUpdate(float deltaTime) = 0;
    virtual void onRender() = 0;
    virtual void onShutdown() = 0;

private:
    ApplicationConfig m_config;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Context> m_context;
    bool m_initialized = false;
    bool m_isRunning = false;
    
    static Application* s_instance;
};

std::unique_ptr<Application> createApplication();

#endif // APPLICATION_HH
