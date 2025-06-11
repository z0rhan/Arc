#ifndef APPLICATION_HH
#define APPLICATION_HH

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace PhysicsEngine
{
    class Application
    {
        public:
            Application();
            virtual ~Application();

            bool init();
            void run();

        private:
            GLFWwindow* initializeGLFW();
            static void updateWindowSize(GLFWwindow* window, int width, int height);

        private:
            GLFWwindow* m_window;
    };
}

#endif // APPLICATION_HH
