# https://github.com/dominiksalvet/cpurast

cmake_minimum_required(VERSION 3.0.0)
project(cpurast CXX)

find_package(SDL2 REQUIRED)

add_library(cpurast
    cpurast/cpurast.cpp
)
target_include_directories(cpurast PUBLIC cpurast)

add_executable(triangle examples/triangle/main.cpp)
target_include_directories(triangle PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(triangle PRIVATE ${SDL2_LIBRARIES} cpurast)
