// https://github.com/dominiksalvet/cpurast

#include "renderer.hpp"
#include <cassert>

namespace cr
{
    renderer::renderer(framebuf& fb, viewport& vp, const vertex_shader* vs, const fragment_shader* fs) :
        fb(fb),
        vp(vp),
        vs(vs),
        fs(fs) {}
    
    void renderer::render_point(const vector<float>& v)
    {
        position pos = vs->run(v, shader_pipe); // run vertex shader

        if (!pos.is_normalized()) { // clipping
            return;
        }

        // compute final framebuffer coordinates
        size_t x = get_framebuf_x(pos.x);
        size_t y = get_framebuf_y(pos.y);

        color col = fs->run(shader_pipe); // run fragment shader

        // write to framebuffer
        fb.write(x, y, col, pos.z);
    }

    void renderer::render_line(const vector<float>& v1, const vector<float> v2)
    {
        render_point(v1);
        render_point(v2);
    }

    void renderer::render_triangle(const vector<float>& v1, const vector<float> v2, const vector<float> v3)
    {
        render_point(v1);
        render_point(v2);
        render_point(v3);
    }

    void renderer::set_vs(const vertex_shader* vs) {
        this->vs = vs;
    }

    void renderer::set_fs(const fragment_shader* fs) {
        this->fs = fs;
    }

    size_t renderer::get_framebuf_x(float x) const
    {
        assert(x >= -1.f && x <= 1.f);

        // each pixel is addressable by its center
        return (x * vp.width - x + vp.width) / 2 + vp.x;
    }

    size_t renderer::get_framebuf_y(float y) const
    {
        assert(y >= -1.f && y <= 1.f);

        // each pixel is addressable by its center
        return (y * vp.height - y + vp.height) / 2 + vp.y;
    }
}
