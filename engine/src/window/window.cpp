#include "window.h"
#include "defines.h"
#include "core/logger.h"

#include <GLFW/glfw3.h>

bool windowStarup(WindowState* windowState, const char* applicationName,
                    int32_t x, int32_t  y,
                    int32_t width, int32_t height)
{
    if (!glfwInit())
    {
        ARC_FATAL("Failed to initialize GLFW!");
        return FALSE;
    }

    windowState->window_ = glfwCreateWindow(width, height, applicationName, 0, 0);

    if (!windowState->window_)
    {
        ARC_FATAL("Failed to initialize window!");
        glfwTerminate();
        return FALSE;
    }

    glfwSetWindowPos(windowState->window_, x, y);
    glfwMakeContextCurrent(windowState->window_);

    return TRUE;
}

void windowShutdown(WindowState* windowState)
{
    if (windowState->window_)
    {
        glfwDestroyWindow(windowState->window_);
        windowState->window_ = nullptr;
    }

    glfwTerminate();
}

bool windowPumpMsg(WindowState* state)
{
    if (glfwWindowShouldClose(state->window_))
    {
        return FALSE;
    }

    glfwPollEvents();
    return TRUE;
}

void windowSwapBuffers(WindowState* state)
{
    glfwSwapBuffers(state->window_);
}
