// https://github.com/dominiksalvet/cpurast

#include "context.hpp"
#include <stdexcept>

namespace cr
{
    context::context(cr::canvas* canvas) :
        canvas(canvas),
        framebuf(canvas->get_width(), canvas->get_height()),
        viewp_x(0),
        viewp_y(0),
        viewp_width(canvas->get_width()),
        viewp_height(canvas->get_height()) {}

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
    
    void context::set_viewport(size_t x, size_t y, size_t width, size_t height)
    {
        if (x + width > framebuf.get_width() || y + height > framebuf.get_height()) {
            throw std::runtime_error("Viewport outside of the framebuffer!");
        }

        viewp_x = x;
        viewp_y = y;
        viewp_width = width;
        viewp_height = height;
    }
}
