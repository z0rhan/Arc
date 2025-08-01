set(ENGINESOURCE
    # Core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/factory.cpp

    # Platform
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_win32.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_linux.cpp

    # Window
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window/window_glfw.cpp

    # Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/GL_context_glfw.cpp

    # Event

    # Glad
    ${CMAKE_SOURCE_DIR}/vendors/glad/src/glad.c
)

add_library(engine STATIC ${ENGINESOURCE})

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/vendors
        ${CMAKE_SOURCE_DIR}/vendors/glad/include
)

target_link_libraries(engine
    PRIVATE
    ${CMAKE_SOURCE_DIR}/vendors/GLFW/lib/libglfw3.a
)
