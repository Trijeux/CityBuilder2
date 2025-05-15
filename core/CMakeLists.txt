file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(core ${SRC_FILES} ${HEADER_FILES})

target_include_directories(core PUBLIC include/)
target_link_libraries(core PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)

if(ENABLE_PROFILING)
    target_link_libraries(core PRIVATE Tracy::TracyClient)
    target_compile_definitions(core PRIVATE TRACY_ENABLE=1)
endif(ENABLE_PROFILING)