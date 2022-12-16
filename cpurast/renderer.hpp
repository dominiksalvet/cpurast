// https://github.com/dominiksalvet/cpurast

#pragma once

#include <cstddef>
#include "framebuf.hpp"
#include "viewport.hpp"
#include "shader.hpp"

namespace cr
{
    class renderer
    {
    public:
        renderer(framebuf& fb, viewport& vp, const vertex_shader* vs, const fragment_shader* fs);

        void render_point(const vector<float>& v);
        void render_line(const vector<float>& v1, const vector<float> v2);
        void render_triangle(const vector<float>& v1, const vector<float> v2, const vector<float> v3);

        void set_vs(const vertex_shader* vs);
        void set_fs(const fragment_shader* fs);

    private:
        // transform normalized coordinates [0, 1] to framebuffer coordinates
        size_t get_framebuf_x(float x) const;
        size_t get_framebuf_y(float y) const;

        framebuf& fb;
        viewport& vp;

        const vertex_shader* vs;
        const fragment_shader* fs;

        vector<float> shader_pipe; // helper structure for shader attributes
    };
}
