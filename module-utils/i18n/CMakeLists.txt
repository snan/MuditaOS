add_library(i18n STATIC)

target_sources(i18n
    PRIVATE
        i18n.cpp
        i18nImpl.hpp
    PUBLIC
        include/i18n/i18n.hpp
)

target_include_directories(i18n
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(i18n
    PRIVATE 
        json::json
        log-api
        module-os
        purefs-paths
)

if (${ENABLE_TESTS})
    add_subdirectory(tests)
endif()
