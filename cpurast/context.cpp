// https://github.com/dominiksalvet/cpurast

#include "context.hpp"

namespace cr
{
    context::context(cr::canvas* canvas) :
        canvas(canvas),
        framebuf(canvas->get_width(), canvas->get_height()) {}

    void context::enable_depth_test() {
        framebuf.enable_depth_test();
    }

    void context::update_canvas() {
        canvas->draw(framebuf.get_color_buf(), framebuf.get_width(), framebuf.get_height());
    }

    void context::set_clear_color(color clear_color) {
        framebuf.set_clear_color(clear_color);
    }
    
    void context::clear_framebuf(bool clear_color, bool clear_depth) {
        framebuf.clear(clear_color, clear_depth);
    }
    
    void context::set_canvas(cr::canvas* canvas)
    {
        this->canvas = canvas;
        framebuf.resize(canvas->get_width(), canvas->get_height());
    }
}
