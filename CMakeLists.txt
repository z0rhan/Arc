cmake_minimum_required(VERSION 3.31)
project(Arc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(engine)
add_subdirectory(sandbox)

# Tests
option(BUILD_TESTING "Enable testing" ON)
if (BUILD_TESTING)
    enable_testing()

    add_subdirectory(vendors/gtest)

    set(TEST_SOURCE
        tests/test_logger.cpp
        tests/test_application.cpp
        tests/test_factory.cpp
        tests/test_event.cpp
    )
    add_executable(my_test ${TEST_SOURCE})

    target_include_directories(my_test PRIVATE
        ${CMAKE_SOURCE_DIR}/engine/src
    )

    target_link_libraries(my_test PRIVATE
        GTest::gtest_main
        engine
    )

    include(GoogleTest)
    gtest_discover_tests(my_test)
endif()


