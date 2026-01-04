cmake_minimum_required(VERSION 3.16)

project(Sim
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable warnings
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Build executable
add_executable(sim
    sim.cpp
    Grid.cpp
    Puck.cpp
)

target_include_directories(sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})