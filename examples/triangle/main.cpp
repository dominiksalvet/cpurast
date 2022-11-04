// https://github.com/dominiksalvet/swrast

#include "swrast.hpp"
#include "SDL.h"
#include <iostream>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Surface* surface;
    uint32_t* pixels;
    bool shouldExit = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL2!" << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("swrast - triangle",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Failed to create SDL2 window!" << std::endl;
        SDL_Quit();
        return -1;
    }

    surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        std::cerr << "Failed to obtain SDL2 window surface!" << std::endl;
        SDL_Quit();
        return -1;
    }
    pixels = (uint32_t*)surface->pixels;

    while (!shouldExit)
    {
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

        int x = surface->w / 10;
        int y = surface->h / 30;

        int width = surface->w;

        pixels[x + y * width] = 0xffffffff;

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
