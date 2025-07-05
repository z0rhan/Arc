set(ENGINESOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_win32.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_linux.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window/window.cpp
)

add_library(engine SHARED ${ENGINESOURCE})

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/vendors

)

target_link_libraries(engine
    PRIVATE
    ${CMAKE_SOURCE_DIR}/vendors/GLFW/lib/libglfw.so.3.4
)
