#include <core/logger.h>
#include <core/asserts.h>

#include <platform/platform.h>
#include <window/window.h>

int main()
{
    ARC_FATAL("A test message: {}", "Testing");
    ARC_ERROR("A test message: {} {}", "Testing", 1);
    ARC_WARN("A test message: {}", "Testing");
    ARC_INFO("A test message: {}", "Testing");

    WindowState state;
    if (windowStarup(&state, "Test", 0, 0, 800, 600))
    {
        while (TRUE)
        {
            if (!windowPumpMsg(&state))
            {
                break;
            }
            windowSwapBuffers(&state);
        }
    }

    return 0;
}
