// https://github.com/dominiksalvet/cpurast

#include "context.hpp"

namespace cr
{
    context::context(cr::canvas& canvas) :
        canvas(canvas),
        framebuf(canvas.get_width(), canvas.get_height()) {}
    
    void context::set_canvas(cr::canvas& canvas)
    {
        this->canvas = canvas;
        framebuf.resize(canvas.get_width(), canvas.get_height());
    }

    void context::enable_depth_test() {
        framebuf.enable_depth_test();
    }
}
