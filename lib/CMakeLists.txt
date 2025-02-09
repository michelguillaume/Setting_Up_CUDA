cmake_minimum_required(VERSION 3.10.2)

project(SettingUpUtils VERSION 1.0 LANGUAGES C)

file(GLOB LIB_SOURCES "src/*.c")
file(GLOB LIB_HEADERS "include/*.h")

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
