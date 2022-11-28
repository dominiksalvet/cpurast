// https://github.com/dominiksalvet/cpurast

#include "SDL.h"
#include "cpurast.hpp"
#include <iostream>
#include <chrono>
#include <thread>

namespace sc = std::chrono;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int FRAMERATE = 60;
const sc::nanoseconds FRAMETIME(sc::duration_cast<sc::nanoseconds>(sc::seconds(1)) / FRAMERATE);

int main(int argc, char* argv[])
{
    using clock = sc::high_resolution_clock;

    SDL_Window* window;
    SDL_Surface* surface;
    bool shouldExit = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL2!" << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("cpurast - triangle example",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Failed to create SDL2 window!" << std::endl;
        SDL_Quit(); return -1;
    }

    surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        std::cerr << "Failed to obtain SDL2 window surface!" << std::endl;
        SDL_Quit(); return -1;
    }

    // initialize cpurast rasterizer
    cr::context cr_context = cr::context(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!shouldExit)
    {
        auto time_start = clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    surface = SDL_GetWindowSurface(window);
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    shouldExit = true;
                }
            }

            if (event.type == SDL_QUIT) {
                shouldExit = true;
            }
        }

        SDL_UpdateWindowSurface(window);

        sc::nanoseconds cur_frametime = clock::now() - time_start;
        if (cur_frametime < FRAMETIME) {
            std::this_thread::sleep_for(FRAMETIME - cur_frametime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
