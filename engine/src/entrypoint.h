#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "core/logger.h"
#include "core/application.h"
#include <memory>

extern std::unique_ptr<Application> createApplication();

int main()
{
    auto app = createApplication();

    app->run();

    return 0;
}

#endif //ENTRYPOINT_H
