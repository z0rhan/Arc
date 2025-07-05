#ifndef WINDOW_HH
#define WINDOW_HH

#include "defines.h"

#include <GLFW/glfw3.h>

struct WindowState 
{
    GLFWwindow* window_;
};

bool windowStarup(WindowState* windowState, const char* applicationName,
                    int32_t x, int32_t  y,
                    int32_t width, int32_t height);
void windowShutdown(WindowState* state);

bool windowPumpMsg(WindowState* state);

// Required for GLFW
void windowSwapBuffers(WindowState* state);

#endif // WINDOW_HH
