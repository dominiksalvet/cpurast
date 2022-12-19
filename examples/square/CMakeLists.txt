# https://github.com/dominiksalvet/cpurast

cmake_minimum_required(VERSION 3.0.0)
project(square CXX)

find_package(SDL2 REQUIRED)

add_executable(square
    main.cpp
)
target_include_directories(square PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CPURAST_INCLUDE_DIR}
    ${CPURAST_SDL_INCLUDE_DIR}
    ${SHADERS_INCLUDE_DIR}
)
target_link_libraries(square PRIVATE
    ${SDL2_LIBRARIES}
    cpurast
    cpurast_sdl
)
