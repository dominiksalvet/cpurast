// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include "viewport.hpp"
#include "shader.hpp"
#include "rasterizer.hpp"

namespace cr
{
    class renderer
    {
    public:
        renderer(framebuf& fb, const vertex_shader* vs, const fragment_shader* fs);

        // main render functions
        void render_point(const vector<float>& v);
        void render_line(const vector<float>& v1, const vector<float>& v2);
        // this function also supports adjacent triangles rendering (no gaps, no overlaps)
        void render_triangle(const vector<float>& v1, const vector<float>& v2, const vector<float>& v3);

        void set_vs(const vertex_shader* vs);
        void set_viewport(unsigned x, unsigned y, unsigned width, unsigned height);
        void set_interp_enabled(bool interp_enabled);
        void set_fs(const fragment_shader* fs);

    private:
        // transform normalized coordinates [-1, 1] to framebuffer coordinates
        unsigned get_framebuf_x(float x) const;
        unsigned get_framebuf_y(float y) const;

        const vertex_shader* vs;
        vector<float> vertex_attribs[3]; // vertex shader output attributes

        viewport vp; // current viewport properties

        rasterizer rast; // graphics rasterizer
    };
}
