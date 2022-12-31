// https://github.com/dominiksalvet/cpurast

#include "context.hpp"
#include <cassert>
#include "default_shader.hpp"

using std::make_shared;

namespace cr
{
    context::context(cr::canvas* canvas, unsigned canvas_w, unsigned canvas_h) :
        canvas(canvas),
        framebuf(canvas_w, canvas_h),
        v_shader(make_shared<default_vs>()),
        f_shader(make_shared<default_fs>()),
        renderer(framebuf, v_shader.get(), f_shader.get()) {}

    void context::update_canvas() const {
        canvas->draw(framebuf.get_color_buf(), framebuf.get_width(), framebuf.get_height());
    }

    void context::bind_canvas(cr::canvas* canvas) {
        this->canvas = canvas;
    }
    
    void context::resize_framebuf(unsigned new_width, unsigned new_height) {
        framebuf.resize(new_width, new_height);
    }

    void context::clear_framebuf(bool clear_color, bool clear_depth) {
        framebuf.clear(clear_color, clear_depth);
    }

    void context::set_clear_color(float r, float g, float b)
    {
        assert(r >= 0.f && r <= 1.f);
        assert(g >= 0.f && g <= 1.f);
        assert(b >= 0.f && b <= 1.f);

        framebuf.set_clear_color({r, g, b});
    }
    
    void context::set_viewport(unsigned x, unsigned y, unsigned width, unsigned height)
    {
        assert(x < framebuf.get_width() && y < framebuf.get_height());
        assert(width > 0 && height > 0);
        assert(x + width <= framebuf.get_width() && y + height <= framebuf.get_height());

        renderer.set_viewport(x, y, width, height);
    }

    void context::enable_depth_test() {
        framebuf.enable_depth_test();
    }
    
    void context::disable_depth_test() {
        framebuf.disable_depth_test();
    }

    void context::enable_interpolation() {
        renderer.set_interp_enabled(true);
    }

    void context::disable_interpolation() {
        renderer.set_interp_enabled(false);
    }

    void context::bind_vertex_shader(const shared_ptr<const vertex_shader>& v_shader)
    {
        this->v_shader = v_shader; // share ownership
        renderer.set_vs(v_shader.get());
    }

    void context::bind_fragment_shader(const shared_ptr<const fragment_shader>& f_shader)
    {
        this->f_shader = f_shader; // share ownership
        renderer.set_fs(f_shader.get());
    }

    void context::draw_point(const vector<float>& v) {
        renderer.render_point(v);
    }

    void context::draw_line(const vector<float>& v1, const vector<float>& v2) {
        renderer.render_line(v1, v2);
    }

    void context::draw_triangle(const vector<float>& v1, const vector<float>& v2, const vector<float>& v3) {
        renderer.render_triangle(v1, v2, v3);
    }
}
