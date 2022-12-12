// https://github.com/dominiksalvet/cpurast

#include "sdl_canvas.hpp"
#include <cassert>
#include <limits>
#include <stdexcept>

using std::numeric_limits;

namespace cr
{
    sdl_canvas::sdl_canvas(SDL_Surface* const surface) :
        surface(surface),
        surface_locking(SDL_MUSTLOCK(surface))
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

    void sdl_canvas::draw(const vector<color>& color_buf, size_t width, size_t height)
    {
        assert(get_width() == width && get_height() == height);

        if (surface_locking) {
            SDL_LockSurface(surface);
        }
        
        Uint32* const pixels = static_cast<Uint32*>(surface->pixels);
        const size_t total_size = width * height;

        // we can perform linear for-loop because of restrictions in constructor
        for (size_t i = 0; i < total_size; i++)
        {
            color cur_color = color_buf[i];

            // float to 8-bit for each of RGB components
            Uint8 r = cur_color.r * numeric_limits<Uint8>::max();
            Uint8 g = cur_color.g * numeric_limits<Uint8>::max();
            Uint8 b = cur_color.b * numeric_limits<Uint8>::max();

            // 8-bit RGB components to current SDL pixel format
            Uint32 pixel = SDL_MapRGB(surface->format, r, g ,b);

            // drawing one pixel
            pixels[i] = pixel;
        }

        if (surface_locking) {
            SDL_UnlockSurface(surface);
        }
    }

    size_t sdl_canvas::get_width() {
        return surface->w;
    }
    
    size_t sdl_canvas::get_height() {
        return surface->h;
    }
}
