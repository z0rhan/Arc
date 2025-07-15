#include "core/logger.h"
#include <sstream>
#include <string>

#include <gtest/gtest.h>

class LoggerTest : public ::testing::Test 
{
protected:
    void SetUp() override {
        initializeLogger();
    }
    
    void TearDown() override {
        shutdownLogger();
    }
};

// Initialization and Shutdown has not been implemented yet
TEST_F(LoggerTest, InitializationAndShutdown)
{
    EXPECT_TRUE(initializeLogger());
    EXPECT_NO_THROW(shutdownLogger());
}

TEST_F(LoggerTest, FatalLogging)
{
    std::stringstream buffer;
    // Read from cerr, not cout
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());
    
    ARC_FATAL("Test fatal message");
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("FATAL") != std::string::npos);
    EXPECT_TRUE(output.find("Test fatal message") != std::string::npos);
    
    std::cerr.rdbuf(old);
}

TEST_F(LoggerTest, ErrorLogging)
{
    std::stringstream buffer;
    // Read from cerr, not cout
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());
    
    ARC_ERROR("Test error message");
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("ERROR") != std::string::npos);
    EXPECT_TRUE(output.find("Test error message") != std::string::npos);
    
    std::cerr.rdbuf(old);
}

TEST_F(LoggerTest, LogFormatting)
{
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    int value = 42;
    ARC_INFO("Test value: {}", value);
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("42") != std::string::npos);
    
    std::cout.rdbuf(old);
}

TEST_F(LoggerTest, LogLevelFiltering)
{
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    ARC_TRACE("Trace message");
    ARC_DEBUG("Debug message");
    ARC_INFO("Info message");
    
    std::string output = buffer.str();
    
    #if ARC_TRACE_ENABLED
    EXPECT_TRUE(output.find("Trace message") != std::string::npos);
    #endif
    
    #if ARC_DEBUG_ENABLED
    EXPECT_TRUE(output.find("Debug message") != std::string::npos);
    #endif
    
    #if ARC_INFO_ENABLED
    EXPECT_TRUE(output.find("Info message") != std::string::npos);
    #endif
    
    std::cout.rdbuf(old);
}
