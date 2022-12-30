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
        renderer(framebuf& fb, const vertex_shader* vs, const fragment_shader* fs);

        // main render functions
        void render_point(const vector<float>& v);
        void render_line(const vector<float>& v1, const vector<float>& v2);
        // this function also supports adjacent triangles rendering
        void render_triangle(const vector<float>& v1, const vector<float>& v2, const vector<float>& v3);

        void set_vs(const vertex_shader* vs);
        void set_fs(const fragment_shader* fs);
        void set_viewport(unsigned x, unsigned y, unsigned width, unsigned height);

    private:
        // transform normalized coordinates [-1, 1] to framebuffer coordinates
        unsigned get_framebuf_x(float x) const;
        unsigned get_framebuf_y(float y) const;

        // rasterization functions based on Bresenham's line algorithm
        void rasterize_line(int x1, int y1, float d1, int x2, int y2, float d2);
        void rasterize_triangle(int x1, int y1, float d1, int x2, int y2, float d2, int x3, int y3, float d3);

        // initialize interpolation (call once before a batch of interpolation calls)
        void init_interpolation(unsigned index, const vector<float>& v1, unsigned total_steps);
        // interpolates depths and attributes based on current step, uses member arrays based on index
        void interpolation(unsigned index, float d1, const vector<float>& v1, float d2, const vector<float>& v2, unsigned cur_step);

        void process_fragment(unsigned x, unsigned y, float d, const vector<float>& v);

        framebuf& fb;
        const vertex_shader* vs;
        const fragment_shader* fs;

        viewport vp; // current viewport properties

        vector<float> vertex_attribs[3]; // vertex shader output attributes
        float interp_step[3]; // prepared interpolation steps
        float interp_depth[3]; // interpolated depths
        vector<float> interp_attribs[3]; // interpolated attributes
    };
}
