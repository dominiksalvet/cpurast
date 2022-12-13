// https://github.com/dominiksalvet/cpurast

#pragma once

#include "color.hpp"
#include <vector>
#include <cstddef>

namespace cr
{
    // interface for displaying graphics on a canvas (e.g., content of window)
    class canvas
    {
    public:
        virtual ~canvas() = default;

        // canvas resolution and color buffer resolution must be the same
        virtual void draw(const std::vector<color>& color_buf, size_t width, size_t height) = 0;

        // return sizes of canvas in number of pixels
        virtual size_t get_width() = 0;
        virtual size_t get_height() = 0;
    };
}
