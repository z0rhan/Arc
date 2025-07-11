#ifndef GLFW_INTEGRATION_HH
#define GLFW_INTEGRATION_HH

#include "event_key.h"
#include "event_dispatcher.h"
#include <GLFW/glfw3.h>

namespace GLFWIntegration {

inline void setupKeyEvents(GLFWwindow* window) {
    // Key press/release callback
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        const KeyCode keyCode = static_cast<KeyCode>(key);
        
        switch (action) {
            case GLFW_PRESS:
                EventDispatcher::dispatch(KeyPressedEvent(keyCode, 0, mods));
                break;
            case GLFW_RELEASE:
                EventDispatcher::dispatch(KeyReleasedEvent(keyCode, mods));
                break;
            case GLFW_REPEAT:
                EventDispatcher::dispatch(KeyPressedEvent(keyCode, 1, mods));
                break;
        }
    });

    // Character input callback (for text input)
    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
        EventDispatcher::dispatch(KeyTypedEvent(static_cast<KeyCode>(codepoint)));
    });
}

} // namespace GLFWIntegration

#endif // GLFW_INTEGRATION_HH
