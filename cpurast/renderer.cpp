// https://github.com/dominiksalvet/cpurast

#include "renderer.hpp"
#include <cassert>

namespace cr
{
    renderer::renderer(framebuf& fb, const vertex_shader* vs, const fragment_shader* fs) :
        vs(vs),
        vp{0, 0, fb.get_width(), fb.get_height()},
        rast(vertex_attribs, fb, fs) {}
    
    void renderer::render_point(const vector<float>& v)
    {
        // run vertex shader
        const position pos = vs->run(v, vertex_attribs[0]);

        if (!pos.is_normalized()) { // clipping
            return;
        }

        // compute framebuffer coordinates
        const unsigned x = get_framebuf_x(pos.x);
        const unsigned y = get_framebuf_y(pos.y);

        rast.fill_point(x, y, pos.z);
    }

    void renderer::render_line(const vector<float>& v1, const vector<float>& v2)
    {
        // run vertex shader
        const position pos1 = vs->run(v1, vertex_attribs[0]);
        const position pos2 = vs->run(v2, vertex_attribs[1]);

        // simple clipping (all or nothing)
        if (!pos1.is_normalized() || !pos2.is_normalized()) {
            return;
        }

        // compute endpoint framebuffer coordinates
        const int x1 = get_framebuf_x(pos1.x);
        const int y1 = get_framebuf_y(pos1.y);
        const int x2 = get_framebuf_x(pos2.x);
        const int y2 = get_framebuf_y(pos2.y);

        rast.fill_line(x1, y1, pos1.z, x2, y2, pos2.z);
    }

    void renderer::render_triangle(const vector<float>& v1, const vector<float>& v2, const vector<float>& v3)
    {
        // run vertex shader
        const position pos1 = vs->run(v1, vertex_attribs[0]);
        const position pos2 = vs->run(v2, vertex_attribs[1]);
        const position pos3 = vs->run(v3, vertex_attribs[2]);

        // simple clipping (all or nothing)
        if (!pos1.is_normalized() || !pos2.is_normalized() || !pos3.is_normalized()) {
            return;
        }

        // compute endpoint framebuffer coordinates
        const int x1 = get_framebuf_x(pos1.x);
        const int y1 = get_framebuf_y(pos1.y);
        const int x2 = get_framebuf_x(pos2.x);
        const int y2 = get_framebuf_y(pos2.y);
        const int x3 = get_framebuf_x(pos3.x);
        const int y3 = get_framebuf_y(pos3.y);

        rast.fill_triangle(x1, y1, pos1.z, x2, y2, pos2.z, x3, y3, pos3.z);
    }

    void renderer::set_vs(const vertex_shader* vs) {
        this->vs = vs;
    }

    void renderer::set_viewport(unsigned x, unsigned y, unsigned width, unsigned height) {
        vp = {x, y, width, height};
    }

    void renderer::set_interp_enabled(bool interp_enabled) {
        rast.set_interp_enabled(interp_enabled);
    }

    void renderer::set_fs(const fragment_shader* fs) {
        rast.set_fs(fs);
    }

    unsigned renderer::get_framebuf_x(float x) const
    {
        assert(x >= -1.f && x <= 1.f);

        unsigned rel_x = ((x + 1) * vp.width) / 2;

        // last position interval is closed from both sides
        if (rel_x == vp.width) {
            rel_x--;
        }

        return vp.x + rel_x;
    }

    unsigned renderer::get_framebuf_y(float y) const
    {
        assert(y >= -1.f && y <= 1.f);

        unsigned rel_y = ((y + 1) * vp.height) / 2;

        // last position interval is closed from both sides
        if (rel_y == vp.height) {
            rel_y--;
        }

        return vp.y + rel_y;
    }
}
