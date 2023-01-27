#root CMake
cmake_minimum_required(VERSION 3.16)
project(sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

add_library(Engine INTERFACE)
target_link_directories(Engine INTERFACE GapBuffer Buffer File)



