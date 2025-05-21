cmake_minimum_required(VERSION 3.31)

option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)
option(ENABLE_TESTS "Enable Tests" OFF)

if (ENABLE_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES "testing")
endif (ENABLE_TESTS)

if(ENABLE_PROFILING)
    list(APPEND VCPKG_MANIFEST_FEATURES "profiling")
endif(ENABLE_PROFILING)

project(CityBuilder2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (ENABLE_TESTS)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif (ENABLE_TESTS)

if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

add_subdirectory(core/)
add_subdirectory(api/)
add_subdirectory(game/)

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/resources")
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(CityBuilder2 main.cc)

target_link_libraries(CityBuilder2 PRIVATE core api game)