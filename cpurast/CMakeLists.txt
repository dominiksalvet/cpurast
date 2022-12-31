# https://github.com/dominiksalvet/cpurast

cmake_minimum_required(VERSION 3.0.0)
project(cpurast CXX)

add_library(cpurast
    context.cpp
    framebuf.cpp
    renderer.cpp
    rasterizer.cpp
)

set(CPURAST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
