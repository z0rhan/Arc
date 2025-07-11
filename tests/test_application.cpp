#include "core/application.h"
#include "core/logger.h"
#include <memory>

#include <gtest/gtest.h>

class TestApplication : public Application
{
public:
    TestApplication(const ApplicationConfig& config) : Application(config) {}
    
    bool initializeCalled = false;
    bool updateCalled = false;
    bool renderCalled = false;
    bool shutdownCalled = false;
    
    bool onInitialize() override
    {
        initializeCalled = true;
        return true;
    }
    
    void onUpdate(float deltaTime) override
    {
        updateCalled = true;
    }
    
    void onRender() override
    {
        renderCalled = true;
    }
    
    void onShutdown() override
    {
        shutdownCalled = true;
    }
};

class ApplicationTest : public ::testing::Test 
{
protected:
    void SetUp() override
    {
        config =
        {
            "Test Application", // name
            800,                // widht
            600,                // height
            100,                // xPos
            100                 // yPos
        };
    }
    
    ApplicationConfig config;
};

TEST_F(ApplicationTest, ApplicationCreation)
{
    auto app = std::make_unique<TestApplication>(config);
    ASSERT_NE(app, nullptr);

    app->shutdown();
}

TEST_F(ApplicationTest, ApplicationInitialization)
{
    auto app = std::make_unique<TestApplication>(config);
    ASSERT_TRUE(app->initialize());
    EXPECT_TRUE(app->initializeCalled);

    app->shutdown();
}

TEST_F(ApplicationTest, ApplicationLifecycle)
{
    auto app = std::make_unique<TestApplication>(config);
    ASSERT_TRUE(app->initialize());
    
    app->onUpdate(0.016f);
    app->onRender();
    
    EXPECT_TRUE(app->updateCalled);
    EXPECT_TRUE(app->renderCalled);
    
    app->shutdown();
    EXPECT_TRUE(app->shutdownCalled);
}

TEST_F(ApplicationTest, InvalidConfigHandling)
{
    ApplicationConfig invalidConfig =
    {
        nullptr,
        -1,
        -1,
        -1,
        -1
    };
    
    auto app = std::make_unique<TestApplication>(invalidConfig);

    // Currently returns false
    // May change
    EXPECT_FALSE(app->initialize());
}

TEST_F(ApplicationTest, ApplicationSingleton)
{
    auto app1 = std::make_unique<TestApplication>(config);
    auto app2 = std::make_unique<TestApplication>(config);
    
    // Both should be able to initialize, but the second overwrites the first
    bool init1 = app1->initialize();
    EXPECT_TRUE(init1);
    
    // When the second app is created, it becomes the active singleton
    bool init2 = app2->initialize();
    EXPECT_TRUE(init2);
    
    // Clean up properly
    app2->shutdown();
    app1->shutdown();
}
