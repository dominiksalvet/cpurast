// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include "canvas.hpp"

namespace cr
{
    class context
    {
    public:
        context(cr::canvas& canvas);

        void set_canvas(cr::canvas& canvas);
        void enable_depth_test();

    private:
        cr::canvas& canvas; // canvas for drawing pixels
        cr::framebuf framebuf; // framebuffer for rendering
    };
}
