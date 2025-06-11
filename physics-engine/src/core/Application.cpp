#include "Application.h"
#include "GLFW/glfw3.h"

#include <iostream>

static constexpr int s_widht = 800;
static constexpr int s_height = 600;

namespace PhysicsEngine
{
    Application::Application()
    {
    }

    Application::~Application()
    {
        if (m_window)
        {
            glfwDestroyWindow(m_window);
        }
        glfwTerminate();
    }

    bool Application::init()
    {
        m_window = initializeGLFW();

        if (!m_window)
        {
            std::cerr << "Failed to create window\n";
            return false;
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            return false;
        }

        glViewport(0, 0, s_widht, s_height);
        glfwSetFramebufferSizeCallback(m_window, updateWindowSize);

        return true;
    }

    void Application::run()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

    GLFWwindow* Application::initializeGLFW()
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW\n";
            return nullptr;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(s_widht, s_widht, "Physics-engine", nullptr, nullptr);

        return window;
    }

    void Application::updateWindowSize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}
