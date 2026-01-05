cmake_minimum_required(VERSION 3.16)

project(Sim
    VERSION 1.0
    LANGUAGES CXX
)

find_package(GTest CONFIG REQUIRED)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(sim
    sim.cpp
    Grid.cpp
    Puck.cpp
)

add_executable(unit_test
    unit_test.cpp
    Grid.cpp 
    Puck.cpp
)

target_link_libraries(unit_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_test)

target_include_directories(sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})