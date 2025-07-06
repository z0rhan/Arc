#include "ARC.h"
#include "entrypoint.h"

Application* createApplication()
{
    ApplicationConfig config;
    config.name_ = "Test";
    config.startPosX_ = 100;
    config.startPosY_ = 100;
    config.startWidth_ = 800;
    config.startHeight_ = 600;

    return new Application(config);
}
