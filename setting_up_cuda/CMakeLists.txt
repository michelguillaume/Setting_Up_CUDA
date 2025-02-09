cmake_minimum_required(VERSION 3.10.2)

project(setting_up_cuda VERSION 1.0 LANGUAGES CUDA C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(SOURCES
    src/main.cu
)

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_ARCHITECTURES 52
)

target_link_libraries(${PROJECT_NAME} PRIVATE setting_up_utils)
