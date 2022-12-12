// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include "canvas.hpp"

namespace cr
{
    class context
    {
    public:
        context(cr::canvas* canvas);

        void enable_depth_test();
        void update_canvas();
        void set_clear_color(color clear_color);
        void clear_framebuf(bool clear_color, bool clear_depth);

        void set_canvas(cr::canvas* canvas);
        void set_viewport(size_t x, size_t y, size_t width, size_t height);

    private:
        cr::canvas* canvas; // canvas for drawing pixels
        cr::framebuf framebuf; // framebuffer for rendering

        // viewport properties
        size_t viewp_x;
        size_t viewp_y;
        size_t viewp_width;
        size_t viewp_height;
    };
}
