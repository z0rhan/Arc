#include "GL_context_glfw.h"
#include "core/logger.h"

ContextGLFW::ContextGLFW(GLFWwindow* window):
    m_window(window)
{
}

ContextGLFW::~ContextGLFW()
{

}

bool ContextGLFW::init()
{
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ARC_FATAL("Failed to load glad!");
        return FALSE;
    }

    return TRUE;
}

void ContextGLFW::swapContext()
{
    glfwSwapBuffers(m_window);
}