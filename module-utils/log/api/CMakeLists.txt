add_library(log-api INTERFACE)

target_sources(log-api
    INTERFACE
        log/log.hpp
        log/debug.hpp
)

target_include_directories(log-api
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
