# https://github.com/dominiksalvet/cpurast

cmake_minimum_required(VERSION 3.0.0)
project(cpurast_sdl CXX)

find_package(SDL2 REQUIRED)

add_library(cpurast_sdl
    cpurast_sdl.cpp
)
target_include_directories(cpurast_sdl PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CPURAST_INCLUDE_DIR}
)

set(CPURAST_SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
