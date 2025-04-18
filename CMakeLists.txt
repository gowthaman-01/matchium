cmake_minimum_required(VERSION 3.13)

project(http-server)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 23)

# Collect all source files
file(GLOB_RECURSE SRC_FILES
    src/core/*.cpp
    src/http/*.cpp
    src/net/*.cpp
)

# Add executable
add_executable(httprune main.cpp ${SRC_FILES})

# Optional warnings
target_compile_options(httprune PRIVATE -Wall -Wextra -pedantic)
