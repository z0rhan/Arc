#ifndef WINDOW_GLFW_HH
#define WINDOW_GLFW_HH

#include "window.h"
#include "defines.h"

#include <glad/glad.h>  // Must be included before GLFW
#include <GLFW/glfw3.h>

class WindowGLFW final : public Window
{
public:
    explicit WindowGLFW(const WindowConfig& config);
    ~WindowGLFW() override;

    bool init() override;
    bool shouldWindowClose() override;
    void pollEvents() override;

    inline uint32_t getWidth() const override {return m_config.width_;};
    inline uint32_t getHeight() const override {return m_config.height_;};
    inline GLFWwindow* getWindow() const {return m_window;};

    void setupEventHandle();
private:
    static void GLFWErrorCallBack(int32_t error, const char* desc);

private:
    GLFWwindow* m_window;
    WindowConfig m_config;
};

#endif // WINDOW_GLFW_HH
