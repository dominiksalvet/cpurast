// https://github.com/dominiksalvet/cpurast

#include "SDL.h"
#include "cpurast.hpp"
#include <iostream>
#include <cstring>
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
    uint32_t* pixels;
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
    pixels = (uint32_t*)surface->pixels;

    bool rect_up_dir = false;
    bool rect_left_dir = false;
    int rect_x = 40;
    int rect_y = 40;
    int rect_size = 40;

    while (!shouldExit)
    {
        auto time_start = clock::now();

        // input
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    surface = SDL_GetWindowSurface(window);
                    pixels = (uint32_t*)surface->pixels;
                }
            }

            if (event.type == SDL_QUIT) {
                shouldExit = true;
            }
        }

        // update
        if (rect_up_dir) {
            rect_y--;
            if (rect_y <= 0) {
                rect_up_dir = false;
            }
        } else {
            rect_y++;
            if (rect_y >= surface->h) {
                rect_up_dir = true;
            }
        }

        if (rect_left_dir) {
            rect_x--;
            if (rect_x <= 0) {
                rect_left_dir = false;
            }
        } else {
            rect_x++;
            if (rect_x >= surface->w) {
                rect_left_dir = true;
            }
        }

        // render
        int rect_top = rect_y - rect_size/2;
        int rect_bot = rect_y + rect_size/2;
        int rect_left = rect_x - rect_size/2;
        int rect_right = rect_x + rect_size/2;

        if (rect_top < 0) rect_top = 0;
        if (rect_bot >= surface->h) rect_bot = surface->h - 1;
        if (rect_left < 0) rect_left = 0;
        if (rect_right >= surface->w) rect_right = surface->w - 1;

        std::memset(pixels, 0, surface->h * surface->w * sizeof(uint32_t));
        for (int i = rect_top; i < rect_bot; i++) {
            for (int j = rect_left; j < rect_right; j++) {
                pixels[j + i * surface->w] = 0xffffffff;
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
