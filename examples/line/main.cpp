// https://github.com/dominiksalvet/cpurast

#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <memory>
#include "cpurast.hpp" // cpurast core
#include "cpurast_sdl.hpp" // cpurast SDL canvas
#include <cmath>

// timer stuff
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

constexpr int WINDOW_WIDTH = 480;
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
                               WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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

    // create end points of the line
    std::vector<float> center{.5f, .5f, .5f};
    std::vector<float> circle{1.f, .5f, .5f}; // computed dynamically
    double angle = 0.f;

    // create and set up cpurast context
    cr::context cr_context = cr::context(cr_canvas.get(), surface->w, surface->h);

    bool shouldExit = false;
    while (!shouldExit)
    {
        auto time_start = high_resolution_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    shouldExit = true;
                }
            }

            if (event.type == SDL_QUIT) {
                shouldExit = true;
            }
        }

        cr_context.clear_framebuf(true, false); // clear color buffer

        // draw circling line
        angle += .05f;
        // transform from space [-1, 1] to [0, 1]
        circle[0] = (std::cos(angle) + 1.f) / 2.f;
        circle[1] = (std::sin(angle) + 1.f) / 2.f;
        cr_context.draw_line(center, circle);

        cr_context.update_canvas(); // draw ramebuffer data to SDL canvas
        SDL_UpdateWindowSurface(window); // update SDL window

        // simple timer mechanism (may not be very accurate)
        nanoseconds cur_frametime = high_resolution_clock::now() - time_start;
        if (cur_frametime < FRAMETIME) {
            std::this_thread::sleep_for(FRAMETIME - cur_frametime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
