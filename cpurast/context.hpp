// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include "canvas.hpp"
#include "viewport.hpp"

namespace cr
{
    class context
    {
    public:
        context(cr::canvas* canvas);

        // canvas
        void update_canvas();
        void set_canvas(cr::canvas* canvas);

        // framebuffer
        void enable_depth_test();
        void set_clear_color(float r, float g, float b);
        void clear_framebuf(bool clear_color, bool clear_depth);

        // viewport
        void set_viewport(size_t x, size_t y, size_t width, size_t height);

    private:
        cr::canvas* canvas; // canvas for drawing pixels
        cr::framebuf framebuf; // framebuffer for rendering

        cr::viewport viewport; // current viewport properties
    };
}
