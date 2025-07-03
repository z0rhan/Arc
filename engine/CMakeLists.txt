set(ENGINESOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/logger.cpp
)

add_library(engine SHARED ${ENGINESOURCE})

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(engine
    PRIVATE
)
