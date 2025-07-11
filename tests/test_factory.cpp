#include "window/window.h"
#include "window/window_glfw.h"
#include "core/factory.h"

#include <gtest/gtest.h>
#include <memory>

// Class to initialize config for testing
class FactoryTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        config = {
            "Test window",  // Name
            800,            // Width
            600,            // Height
            100,            // xPos
            100             // yPos
        };
    }

    WindowConfig config;
};

// Test to see if a window is created
TEST_F(FactoryTest, WindowIsCreated)
{
    auto window = EngineFactory::createWindow(config);
    ASSERT_NE(window, nullptr);
}

// Check if the window created is GLFWwindow
TEST_F(FactoryTest, WindowIsGLFWType)
{
    auto window = EngineFactory::createWindow(config);
    auto* glfwWindow = dynamic_cast<WindowGLFW*>(window.get());
    ASSERT_NE(glfwWindow, nullptr);
}

// Check if window can be initialized successfully
TEST_F(FactoryTest, GLFWWindowInitializesSuccessfully)
{
    auto window = EngineFactory::createWindow(config);
    auto* glfwWindow = dynamic_cast<WindowGLFW*>(window.get());
    ASSERT_NE(glfwWindow, nullptr);
    ASSERT_TRUE(glfwWindow->init());
}

// Check if the initial config matches the given config
TEST_F(FactoryTest, WindowMatchesConfig)
{
    auto window = EngineFactory::createWindow(config);
    auto* glfwWindow = dynamic_cast<WindowGLFW*>(window.get());
    ASSERT_NE(glfwWindow, nullptr);
    ASSERT_TRUE(glfwWindow->init());
    ASSERT_EQ(config.width_,  glfwWindow->getWidth());
    ASSERT_EQ(config.height_, glfwWindow->getHeight());
}

// Check if context is created successfully
TEST_F(FactoryTest, ContextIsCreated)
{
    auto window = EngineFactory::createWindow(config);
    ASSERT_NE(window, nullptr);

    auto context = EngineFactory::createContext(window.get());
    ASSERT_NE(context, nullptr);
}

// Check if context initializes sucessfully
TEST_F(FactoryTest, ContextInitializes)
{
    auto window = EngineFactory::createWindow(config);
    ASSERT_NE(window, nullptr);

    bool windowInitResult = window->init();
    ASSERT_TRUE(windowInitResult);

    auto context = EngineFactory::createContext(window.get());
    ASSERT_NE(context, nullptr);

    bool contextInitResult = context->init();
    ASSERT_TRUE(contextInitResult);
}
