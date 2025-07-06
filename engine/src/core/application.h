#ifndef APPLICATION_HH
#define APPLICATION_HH

#include "defines.h"
#include "renderer/GL_context_glfw.h"
#include "window/window_glfw.h"

struct ApplicationConfig
{
    char*       name_;
    int32_t     startWidth_;
    int32_t     startHeight_;
    int32_t     startPosX_;
    int32_t     startPosY_;
};

class Application
{
public:
    explicit Application(const ApplicationConfig& config);
    virtual ~Application();

    void run();
private:
    ApplicationConfig m_config;
    bool m_initialized = false;
    bool m_isRunning = false;
};

Application* createApplication();

#endif // APPLICATION_HH
