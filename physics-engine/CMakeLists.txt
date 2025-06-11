set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/glad/src/glad.c
)

add_library(physics SHARED ${SOURCE})

target_include_directories(physics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/glad/include
)

target_link_libraries(physics
    PRIVATE
        OpenGL::GL
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/GLFW/lib/libglfw3.a
)
