cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico_test C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()
add_subdirectory(lib)
add_subdirectory(main)