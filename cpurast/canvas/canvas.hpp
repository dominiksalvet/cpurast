// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"

namespace cr
{
    // abstract class for displaying graphics on a canvas (part of screen)
    class canvas
    {
    public:
        virtual ~canvas() = default;
        // canvas resolution and color buffer resolution must be the same
        virtual void draw(const color_buf_t& color_buf, size_t width, size_t height) = 0;
    };
}
