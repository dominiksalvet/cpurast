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

// custom vertex shader
class main_vs : public cr::vertex_shader
{
public:
    main_vs(const vector<float>& uniforms) :
        vertex_shader(uniforms) {}

    const cr::vertex& run(const cr::vertex& v) override
    {
        // todo: add vertex shader code
        return v;
    }
};

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

    // create cpurast context
    cr::context cr_context = cr::context(cr_canvas.get());

    // create custom vertex shader
    std::shared_ptr<cr::vertex_shader> vs;
    vs = std::make_shared<main_vs>(std::vector<float>{0.f, 1.f, 2.f});

    // set up context properties
    cr_context.set_clear_color(.3f, .5f, .7f);
    cr_context.bind_vertex_shader(vs);

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
