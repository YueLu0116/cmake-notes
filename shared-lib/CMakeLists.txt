cmake_minimum_required(VERSION 3.10)

project(hello-shared)

# create a shared lib
add_library(print SHARED src/hello.cpp)
add_library(print-so ALIAS print)
target_include_directories(print PUBLIC ${PROJECT_SOURCE_DIR}/include)

# create exe
add_executable(hello-shared src/main.cpp)
target_link_libraries(hello-shared PRIVATE print-so)