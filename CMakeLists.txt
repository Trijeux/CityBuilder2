cmake_minimum_required(VERSION 3.31)
project(CityBuilder2)

set(CMAKE_CXX_STANDARD 20)

option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)

find_package(SFML COMPONENTS Graphics Window Audio System CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

add_subdirectory(core/)
add_subdirectory(api/)
add_subdirectory(game/)

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/resources")
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(CityBuilder2 main.cc)

target_include_directories(CityBuilder2 PRIVATE ${CMAKE_SOURCE_DIR}/external/FastNoiseLite)

target_link_libraries(CityBuilder2 PRIVATE core api game SFML::Graphics SFML::Window SFML::Audio SFML::System)