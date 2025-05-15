file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(game ${SRC_FILES} ${HEADER_FILES})
target_include_directories(game PUBLIC include/)

target_link_libraries(game PRIVATE api core SFML::Graphics SFML::Window SFML::Audio SFML::System)

if(ENABLE_PROFILING)
    target_link_libraries(game PRIVATE Tracy::TracyClient)
    target_compile_definitions(game PRIVATE TRACY_ENABLE=1)
endif(ENABLE_PROFILING)