# https://github.com/dominiksalvet/cpurast

cmake_minimum_required(VERSION 3.0.0)
project(examples CXX)

add_subdirectory(cpurast)
add_subdirectory(cpurast/sdl_canvas)
add_subdirectory(shaders)
add_subdirectory(examples/line)
add_subdirectory(examples/triangle)
