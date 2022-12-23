// https://github.com/dominiksalvet/cpurast

#pragma once

#include "canvas.hpp"
#include <SDL.h>

namespace cr
{
    // SDL canvas used for surface drawing (e.g., window surface)
    // this canvas does not use any OpenGL/DirectX features (at least not directly)
    class sdl_canvas : public canvas
    {
    public:
        // should the SDL surface change, recreate the instance of this class
        sdl_canvas(SDL_Surface* const surface);

        void draw(const std::vector<color>& color_buf, unsigned width, unsigned height) override;

    private:
        SDL_Surface* const surface;
        const bool surface_locking; // surface should be locked before write
    };
}
