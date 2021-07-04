cmake_minimum_required(VERSION 3.10)

project(hello-headers)

set(SOURCE src/hello.cpp src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(hello-headers PRIVATE ${PROJECT_SOURCE_DIR}/include)