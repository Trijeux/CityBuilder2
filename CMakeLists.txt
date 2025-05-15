cmake_minimum_required(VERSION 3.31)
project(CityBuilder2)

set(CMAKE_CXX_STANDARD 20)

option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)

find_package(SFML COMPONENTS Graphics Window Audio System CONFIG REQUIRED)

if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

add_subdirectory(core/)

file(COPY ${CMAKE_SOURCE_DIR}/ressources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(CityBuilder2 main.cc)

target_link_libraries(CityBuilder2 PRIVATE core SFML::Graphics SFML::Window SFML::Audio SFML::System)