// https://github.com/dominiksalvet/cpurast

#include "sdl_canvas.hpp"
#include <cassert>
#include <limits>
#include <stdexcept>

namespace cr
{
    sdl_canvas::sdl_canvas(SDL_Surface* const surface) :
        surface(surface)
    {
        // SDL pixels must be accessible as Uint32 values
        if (surface->format->BytesPerPixel != sizeof(Uint32)) {
            throw std::runtime_error("Unsupported number of bytes per SDL pixel!");
        }

        // SDL pixels must be stored in linear array without gaps
        if (surface->pitch != sizeof(Uint32) * surface->w) {
            throw std::runtime_error("Unsupported SDL pixels row width!");
        }
    }

    void sdl_canvas::draw(const color_buf_t& color_buf, size_t width, size_t height)
    {
        assert(get_width() == width && get_height() == height);

        bool surface_locking = SDL_MUSTLOCK(surface);
        if (surface_locking) {
            SDL_LockSurface(surface);
        }
        
        Uint32* const pixels = static_cast<Uint32*>(surface->pixels);
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++)
            {
                color cur_color = color_buf[y][x];

                assert(cur_color.r >= 0.f && cur_color.r <= 1.f);
                assert(cur_color.g >= 0.f && cur_color.g <= 1.f);
                assert(cur_color.b >= 0.f && cur_color.b <= 1.f);

                // float to 8-bit for each of RGB components
                Uint8 r = cur_color.r * std::numeric_limits<Uint8>::max();
                Uint8 g = cur_color.g * std::numeric_limits<Uint8>::max();
                Uint8 b = cur_color.b * std::numeric_limits<Uint8>::max();

                // 8-bit RGB components to current SDL pixel format
                Uint32 pixel = SDL_MapRGB(surface->format, r, g ,b);

                // drawing one pixel
                pixels[y * surface->w + x] = pixel;
            }
        }

        if (surface_locking) {
            SDL_UnlockSurface(surface);
        }
    }

    size_t sdl_canvas::get_width() {
        assert(surface->w >= 0);

        return surface->w;
    }
    
    size_t sdl_canvas::get_height() {
        assert(surface->h >= 0);

        return surface->h;
    }
}
