set (SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(app ${SOURCE})

target_include_directories(app
    PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/src
)

target_link_libraries(app
    PRIVATE
        engine
)
