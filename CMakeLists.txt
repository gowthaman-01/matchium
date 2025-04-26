cmake_minimum_required(VERSION 3.13)

project(matchium)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 23)

# Collect all source files
file(GLOB_RECURSE SRC_FILES
    src/core/*.cpp
    src/http/*.cpp
    src/net/*.cpp
)

# Add executable
add_executable(matchium main.cpp ${SRC_FILES})

# Optional warnings
target_compile_options(matchium PRIVATE -Wall -Wextra -pedantic)
