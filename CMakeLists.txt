cmake_minimum_required(VERSION 3.10.2)

project(MyCUDAProject VERSION 1.0 LANGUAGES CUDA C)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(lib)
add_subdirectory(setting_up_cuda)
add_subdirectory(setting_up_cpu)
