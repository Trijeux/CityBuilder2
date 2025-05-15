file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(api ${SRC_FILES} ${HEADER_FILES})

target_include_directories(api PUBLIC include/ ${CMAKE_SOURCE_DIR}/external/FastNoiseLite)
target_link_libraries(api PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)

if(ENABLE_PROFILING)
    target_link_libraries(api PRIVATE Tracy::TracyClient)
    target_compile_definitions(api PRIVATE TRACY_ENABLE=1)
endif(ENABLE_PROFILING)