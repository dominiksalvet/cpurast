// https://github.com/dominiksalvet/cpurast

#include "context.hpp"
#include <stdexcept>
#include <cassert>

namespace cr
{
    context::context(cr::canvas* canvas) :
        canvas(canvas),
        framebuf(canvas->get_width(), canvas->get_height()),
        viewport{0, 0, canvas->get_width(), canvas->get_height()} {}

    void context::update_canvas() {
        canvas->draw(framebuf.get_color_buf(), framebuf.get_width(), framebuf.get_height());
    }

    void context::set_canvas(cr::canvas* canvas)
    {
        this->canvas = canvas;
        framebuf.resize(canvas->get_width(), canvas->get_height());
    }

    void context::enable_depth_test() {
        framebuf.enable_depth_test();
    }

    void context::set_clear_color(float r, float g, float b)
    {
        assert(r >= 0.f && r <= 1.f);
        assert(g >= 0.f && g <= 1.f);
        assert(b >= 0.f && b <= 1.f);

        framebuf.set_clear_color({r, g, b});
    }
    
    void context::clear_framebuf(bool clear_color, bool clear_depth) {
        framebuf.clear(clear_color, clear_depth);
    }
    
    void context::set_viewport(size_t x, size_t y, size_t width, size_t height)
    {
        if (x + width > framebuf.get_width() || y + height > framebuf.get_height()) {
            throw std::runtime_error("Viewport outside of the framebuffer!");
        }

        viewport = {x, y, width, height};
    }
}
