#ifndef GL_CONTEXT_GLFW_H
#define GL_CONTEXT_GLFW_H

#include "GL_context.h"
#include "defines.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ContextGLFW final : public Context
{
public:
    explicit ContextGLFW(GLFWwindow* window);
    ~ContextGLFW() override;

    bool init() override;
    void swapContext() override;

private:
    GLFWwindow* m_window;
};

#endif //GL_CONTEXT_GLFW_H
