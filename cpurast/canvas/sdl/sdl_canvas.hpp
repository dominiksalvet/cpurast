// https://github.com/dominiksalvet/cpurast

#pragma once

#include "canvas.hpp"
#include <SDL.h>

namespace cr
{
    // SDL canvas used for surface rendering (e.g., window surface)
    class sdl_canvas : public canvas
    {
    public:
        // should the SDL surface change, recreate the instance of this class
        sdl_canvas(SDL_Surface* const surface);

        void draw(const color_buf_t& color_buf, size_t width, size_t height) override;

        size_t get_width() override;
        size_t get_height() override;

    private:
        SDL_Surface* const surface;
        const bool surface_locking; // surface should be locked before write
    };
}
