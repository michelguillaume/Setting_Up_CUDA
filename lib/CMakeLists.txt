file(GLOB LIB_SOURCES "src/*.c")
file(GLOB LIB_HEADERS "include/*.h")

add_library(square_utils STATIC ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(square_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
