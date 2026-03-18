cmake_minimum_required(VERSION 3.28)
project(ar_overlay C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Tell raylib not to build its example programs
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/raylib)

# Our modules
add_subdirectory(shared)
add_subdirectory(ground)
