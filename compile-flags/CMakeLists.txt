cmake_minimum_required(VERSION 3.10)
project(compile-flags)
add_executable(compile-flags main.cpp)
target_compile_definitions(compile-flags PRIVATE EX3)