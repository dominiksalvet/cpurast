// https://github.com/dominiksalvet/cpurast

#include "context.hpp"
#include <cassert>
#include "empty_vs.hpp"

namespace cr
{
    context::context(cr::canvas* canvas) :
        canvas(canvas),
        framebuf(canvas->get_width(), canvas->get_height()),
        viewport{0, 0, canvas->get_width(), canvas->get_height()},
        vs(std::make_shared<empty_vs>()) {} // empty vertex shader for start

    void context::update_canvas() {
        canvas->draw(framebuf.get_color_buf(), framebuf.get_width(), framebuf.get_height());
    }

    void context::bind_canvas(cr::canvas* canvas)
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
        assert(x + width > framebuf.get_width() && y + height > framebuf.get_height());

        viewport = {x, y, width, height};
    }

    void context::bind_vertex_shader(const shared_ptr<vertex_shader>& vs) {
        this->vs = vs; // share ownership
    }
}
