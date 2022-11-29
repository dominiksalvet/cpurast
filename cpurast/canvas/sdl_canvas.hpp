// https://github.com/dominiksalvet/cpurast

#pragma once

#include "canvas.hpp"
#include <SDL.h>

namespace cr
{
    // SDL canvas used for screen rendering
    class sdl_canvas : public canvas
    {
    public:
        sdl_canvas(SDL_Surface* const surface);
        void draw(const color_buf_t& color_buf, size_t width, size_t height) override;

    private:
        SDL_Surface* const surface;
    };
}
