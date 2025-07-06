#include "core/application.h"
#include "core/logger.h"
#include "entrypoint.h"

const ApplicationConfig c_config
{
    "Sandbox Application",  // name_
    800,                    // startWidth_
    600,                    // startHeight_
    100,                    // startPosX_
    100                     // startPosY_
};

class SandboxApp : public Application
{
public:
    SandboxApp() : Application(c_config) {}

protected:
    bool onInitialize() override
    {
        return true;
    }

    void onUpdate(float deltaTime) override
    {
    }

    void onRender() override
    {
    }

    void onShutdown() override
    {
    }
};

// Engine expects this function to return std::unique_ptr<Application>
std::unique_ptr<Application> createApplication()
{
    return std::make_unique<SandboxApp>();
}