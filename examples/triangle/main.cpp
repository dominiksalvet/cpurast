// https://github.com/dominiksalvet/cpurast

#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <memory>
#include "cpurast.hpp" // cpurast core
#include "cpurast_sdl.hpp" // cpurast SDL canvas

// timer stuff
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr int FRAMERATE = 30;
constexpr nanoseconds FRAMETIME(duration_cast<nanoseconds>(seconds(1)) / FRAMERATE);

void prepare_sdl(SDL_Window** window, SDL_Surface** surface, const char* window_title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL!");
    }

    *window = SDL_CreateWindow(window_title,
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               WINDOW_WIDTH, WINDOW_HEIGHT,
                               SDL_WINDOW_RESIZABLE);
    if (!*window)
    {
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL window!");
    }

    *surface = SDL_GetWindowSurface(*window);
    if (!*surface)
    {
        SDL_DestroyWindow(*window);
        SDL_Quit();
        throw std::runtime_error("Failed to obtain SDL window surface!");
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Surface* surface;

    std::unique_ptr<cr::canvas> cr_canvas;
    try
    {
        // initialize SDL library and create window
        prepare_sdl(&window, &surface, "cpurast example - triangle");

        // initialize cpurast SDL canvas
        cr_canvas = std::make_unique<cr::sdl_canvas>(surface);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    // triangle - vertices attributes
    std::vector<std::vector<float>> vs
    {
        {0.f, 0.f, 0.f}, // bottom left
        {.5f, 1.f, 0.f}, // center top
        {1.f, 0.f, 0.f} // bottom right
    };

    // create and set up cpurast context
    cr::context cr_context = cr::context(cr_canvas.get(), surface->w, surface->h);

    bool shouldExit = false;
    while (!shouldExit)
    {
        auto time_start = high_resolution_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    surface = SDL_GetWindowSurface(window); // get new SDL surface
                    cr_canvas = std::make_unique<cr::sdl_canvas>(surface); // create new canvas
                    cr_context.bind_canvas(cr_canvas.get()); // change canvas in cpurast context
                    cr_context.resize_framebuf(surface->w, surface->h); // resize framebuffer
                    cr_context.set_viewport(0, 0, surface->w, surface->h); // set up viewport
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

        cr_context.clear_framebuf(true, false);
        cr_context.draw_triangle(vs[0], vs[1], vs[2]);
        cr_context.update_canvas();
        SDL_UpdateWindowSurface(window);

        // simple timer mechanism (may not be very accurate)
        nanoseconds cur_frametime = high_resolution_clock::now() - time_start;
        if (cur_frametime < FRAMETIME) {
            std::this_thread::sleep_for(FRAMETIME - cur_frametime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
