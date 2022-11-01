# https://github.com/dominiksalvet/swrast

cmake_minimum_required(VERSION 3.0.0)
project(swrast CXX)

add_library(swrast
    swrast/swrast.cpp
)
target_include_directories(swrast PUBLIC swrast)

add_executable(triangle examples/triangle/main.cpp)
target_link_libraries(triangle PRIVATE swrast)
