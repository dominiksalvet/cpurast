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

    private:
        cr::canvas& canvas; // canvas for drawing pixels
        cr::framebuf framebuf; // framebuffer for rendering
    };
}
