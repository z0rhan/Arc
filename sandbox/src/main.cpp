#include "physics-engine.h"

#include <iostream>

int main()
{
    PhysicsEngine::Application app;

    if (!app.init())
    {
        return EXIT_FAILURE;
    }
    
    app.run();

    return 0;
}
