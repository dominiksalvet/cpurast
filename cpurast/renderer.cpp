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

    }

    void renderer::render_line(const vector<float>& v1, const vector<float> v2)
    {

    }

    void renderer::render_triangle(const vector<float>& v1, const vector<float> v2, const vector<float> v3)
    {

    }

    void renderer::set_vs(const vertex_shader* vs) {
        this->vs = vs;
    }

    void renderer::set_fs(const fragment_shader* fs) {
        this->fs = fs;
    }

    size_t renderer::get_framebuf_x(float x) const
    {
        assert(x >= 0.f && x <= 1.f);

        return x * (vp.width - 1) + vp.x;
    }

    size_t renderer::get_framebuf_y(float y) const
    {
        assert(y >= 0.f && y <= 1.f);

        return y * (vp.height - 1) + vp.y;
    }
}
