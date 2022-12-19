// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include "viewport.hpp"
#include "shader.hpp"

namespace cr
{
    class renderer
    {
    public:
        renderer(framebuf& fb, viewport& vp, const vertex_shader* vs, const fragment_shader* fs);

        // main render functions
        void render_point(const vector<float>& v);
        void render_line(const vector<float>& v1, const vector<float> v2);
        void render_triangle(const vector<float>& v1, const vector<float> v2, const vector<float> v3);

        void set_vs(const vertex_shader* vs);
        void set_fs(const fragment_shader* fs);

    private:
        // transform normalized coordinates [-1, 1] to framebuffer coordinates
        unsigned get_framebuf_x(float x) const;
        unsigned get_framebuf_y(float y) const;

        // line rasterization based on Bresenham's line algorithm
        void rasterize_line(int x1, int y1, float d1, int x2, int y2, float d2);
        // triangle rasterization based on digital differential analyzer (DDA algorithm)
        void rasterize_triangle(int x1, int y1, float d1, int x2, int y2, float d2, int x3, int y3, float d3);

        // returns interpolated depth of two vertices, attributes are interpolated to class member
        float line_interpolation(float d1, float d2, unsigned cur, unsigned total);

        framebuf& fb;
        viewport& vp;

        const vertex_shader* vs;
        const fragment_shader* fs;

        // helper shader structures
        vector<float> vertex_attribs[3];
        vector<float> fragment_attribs;
    };
}
