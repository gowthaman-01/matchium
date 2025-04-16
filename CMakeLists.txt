cmake_minimum_required(VERSION 3.13)

project(http-server)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 23)

# Collect all source files
file(GLOB_RECURSE SERVER_FILES
    src/core/*.cpp
    src/server/*.cpp
)

file(GLOB_RECURSE CLIENT_FILES
    src/core/*.cpp
    src/client/*.cpp
)


# Add executable
add_executable(http_server src/server/main.cpp ${SERVER_FILES})

# Add executable
add_executable(client src/client/main.cpp ${CLIENT_FILES})

# Optional warnings
target_compile_options(http_server PRIVATE -Wall -Wextra -pedantic)
target_compile_options(client PRIVATE -Wall -Wextra -pedantic)
