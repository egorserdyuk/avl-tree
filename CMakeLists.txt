cmake_minimum_required(VERSION 3.13)
project(bin-tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(bin-tree main.cpp)

target_link_libraries(bin-tree ${CMAKE_EXE_LINKER_FLAGS})