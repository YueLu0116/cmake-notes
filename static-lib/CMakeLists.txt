cmake_minimum_required(VERSION 3.10)

project(hello-slib)

# create a library
add_library(print src/hello.cpp)
target_include_directories(print PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(hello-slib src/main.cpp)
target_link_libraries(hello-slib PRIVATE print)