// https://github.com/dominiksalvet/cpurast

#include "cpurast.hpp" // cpurast core
#include "cpurast_sdl.hpp" // cpurast SDL canvas
#include "color_shader.hpp"
#include <iostream>
#include <chrono>
#include <thread>

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
        prepare_sdl(&window, &surface, "cpurast example - square");

        // initialize cpurast SDL canvas
        cr_canvas = std::make_unique<cr::sdl_canvas>(surface);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    // create square vertex attributes
    std::vector<std::vector<float>> v
    {
        {-.5f, -.5f, 0.f, 1.f, 1.f, 1.f}, // left bottom, white
        {-.5f, .5f, 0.f, 1.f, 0.f, 0.f}, // left top, red
        {.5f, .5f, 0.f, 0.f, 1.f, 0.f}, // right top, green
        {.5f, -.5f, 0.f, 0.f, 0.f, 1.f}, // right bottom, blue
    };

    // create cpurast context
    cr::context cr_context = cr::context(*cr_canvas, surface->w, surface->h);
    // use color shaders
    cr_context.bind_vertex_shader(std::make_shared<color_vs>());
    cr_context.bind_fragment_shader(std::make_shared<color_fs>());

    bool shouldExit = false;
    while (!shouldExit)
    {
        auto time_start = high_resolution_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // window resize handling
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    surface = SDL_GetWindowSurface(window); // get new SDL surface
                    cr_canvas = std::make_unique<cr::sdl_canvas>(surface); // create new canvas
                    cr_context.bind_canvas(*cr_canvas); // change canvas in cpurast context
                    cr_context.resize_framebuf(surface->w, surface->h); // resize framebuffer

                    // set up squared viewport
                    int square_x = std::min(surface->w, surface->h);
                    cr_context.set_viewport(0, 0, square_x, square_x);
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

        cr_context.clear_framebuf(true, false); // clear color buffer

        // draw colored square
        cr_context.draw_triangle(v[0], v[1], v[3]);
        cr_context.draw_triangle(v[3], v[1], v[2]);

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
