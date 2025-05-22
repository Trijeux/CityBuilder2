cmake_minimum_required(VERSION 3.31)

option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)
option(ENABLE_TESTS "Enable Tests" OFF)

if (ENABLE_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES "testing")
endif ()

if (ENABLE_PROFILING)
    list(APPEND VCPKG_MANIFEST_FEATURES "profiling")
endif ()

project(CityBuilder2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (ENABLE_TESTS)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif ()

if (ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif ()

add_subdirectory(core/)
add_subdirectory(api/)
add_subdirectory(game/)


add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
        COMMENT "🔄 Copying all resources to build directory"
)


add_executable(CityBuilder2 main.cc)
add_dependencies(CityBuilder2 copy_resources)

target_link_libraries(CityBuilder2 PRIVATE core api game)
