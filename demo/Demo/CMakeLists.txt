cmake_minimum_required(VERSION 3.1)
project(Demo)

set(CMAKE_CXX_STANDARD 14)
message("Current CMAKE_SYSTEM_VERSION = ${CMAKE_SYSTEM_VERSION}")


file(GLOB demo_src
    "*.h"
    "include/*.h"
    "include/stl/*.h"
    "include/stl/containers/*.h"
    "*.cpp"
    "stl/*.cpp"
    "stl/containers/*.cpp"
)

# Enable exceptions (passing -f requires passing -Xclang first)
add_definitions(-Xclang -fcxx-exceptions)

add_executable(demo ${demo_src})