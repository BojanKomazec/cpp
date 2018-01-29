cmake_minimum_required(VERSION 3.1)
project(Demo)

set(CMAKE_CXX_STANDARD 14)


file(GLOB demo_src
    "*.h"
    "include/*.h"
    "include/stl/*.h"
    "include/stl/containers/*.h"
    "*.cpp"
    "stl/*.cpp"
    "stl/containers/*.cpp"
)


add_executable(demo ${demo_src})