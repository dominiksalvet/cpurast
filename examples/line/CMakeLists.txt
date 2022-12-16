# https://github.com/dominiksalvet/cpurast

cmake_minimum_required(VERSION 3.0.0)
project(line CXX)

find_package(SDL2 REQUIRED)

add_executable(line
    main.cpp
)
target_include_directories(line PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CPURAST_INCLUDE_DIR}
    ${CPURAST_SDL_INCLUDE_DIR}
)
target_link_libraries(line PRIVATE
    ${SDL2_LIBRARIES}
    cpurast
    cpurast_sdl
)
