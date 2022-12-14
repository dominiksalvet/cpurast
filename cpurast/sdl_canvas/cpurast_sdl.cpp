// https://github.com/dominiksalvet/cpurast

#include "cpurast_sdl.hpp"
#include <cassert>
#include <limits>
#include <stdexcept>

using std::runtime_error;
using std::numeric_limits;

namespace cr
{
    sdl_canvas::sdl_canvas(SDL_Surface* const surface) :
        surface(surface),
        surface_locking(SDL_MUSTLOCK(surface))
    {
        // SDL pixels must be accessible as Uint32 values
        if (surface->format->BytesPerPixel != sizeof(Uint32)) {
            throw runtime_error("Unsupported number of bytes per SDL pixel!");
        }

        // SDL pixels must be stored in linear array without gaps
        if (surface->pitch != sizeof(Uint32) * surface->w) {
            throw runtime_error("Unsupported SDL pixels row width!");
        }
    }

    void sdl_canvas::draw(const std::vector<color>& color_buf, unsigned width, unsigned height)
    {
        assert(surface->w == width && surface->h == height);

        if (surface_locking) {
            SDL_LockSurface(surface);
        }
        
        Uint32* const pixels = static_cast<Uint32*>(surface->pixels);
        const unsigned total_size = width * height;

        // we can perform linear for-loop because of restrictions in constructor
        for (unsigned i = 0; i < total_size; i++)
        {
            const color cur_color = color_buf[i];

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
}
