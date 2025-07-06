#ifndef WINDOW_GLFW_HH
#define WINDOW_GLFW_HH

#include "window.h"
#include "defines.h"

#include <glad/glad.h>  // Must be included before GLFW
#include <GLFW/glfw3.h>
#include <string>

struct WindowConfig
{
    std::string name_;

    int32_t width_;
    int32_t height_;
    int32_t startPosX_;
    int32_t startPosY_;
};

class WindowGLFW final : public Window
{
public:
    explicit WindowGLFW(const WindowConfig& config);
    ~WindowGLFW() override;

    bool init() override;
    bool shouldWindowClose() override;
    void pollEvents() override;

    inline uint32_t getWidth() const {return m_config.width_;};
    inline uint32_t getHeight() const {return m_config.height_;};
    inline GLFWwindow* getWindow() const {return m_window;};

private:
    static void GLFWErrorCallBack(int32_t error, const char* desc);

private:
    GLFWwindow* m_window;
    WindowConfig m_config;
};

#endif // WINDOW_GLFW_HH
