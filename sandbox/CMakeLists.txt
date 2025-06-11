set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)

set (SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(example-app ${SOURCE})

target_include_directories(example-app
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/physics-engine/src
)

target_link_libraries(example-app
    PRIVATE
        physics
)
