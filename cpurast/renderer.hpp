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

        // rasterization functions based on Bresenham's line algorithm
        void rasterize_line(int x1, int y1, float d1, int x2, int y2, float d2);
        void rasterize_triangle(int x1, int y1, float d1, int x2, int y2, float d2, int x3, int y3, float d3);

        // initialize interpolation (call once before a batch of interpolation calls)
        void init_interpolation(unsigned index, vector<float>& v1, unsigned step_count);
        // interpolates given depths and attributes based on given weight, results are written to given index
        void interpolation(unsigned index, float d1, vector<float>& v1, float d2, vector<float>& v2, float weight2);

        framebuf& fb;
        viewport& vp;

        const vertex_shader* vs;
        const fragment_shader* fs;

        vector<float> vertex_attribs[3]; // vertex shader output attributes

        float interp_step[3]; // prepared interpolation steps
        float interp_depth[3]; // interpolated depths
        vector<float> interp_attribs[3]; // interpolated attributes
    };
}
