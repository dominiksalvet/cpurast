# https://github.com/dominiksalvet/cpurast

cmake_minimum_required(VERSION 3.0.0)
project(cpurast CXX)

add_library(cpurast
    context.cpp
)

target_include_directories(cpurast PUBLIC .)
