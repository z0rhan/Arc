#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "core/logger.h"
#include "core/application.h"

extern Application* createApplication();

int main()
{
    auto* app = createApplication();
    ARC_INFO("New application created")

    ARC_INFO("Application running")
    app->run();

    delete app;
    return 0;
}

#endif //ENTRYPOINT_H
