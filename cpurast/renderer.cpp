// https://github.com/dominiksalvet/cpurast

#include "renderer.hpp"
#include <cassert>
#include <cmath>

using std::abs;
using std::swap;

namespace cr
{
    renderer::renderer(framebuf& fb, viewport& vp, const vertex_shader* vs, const fragment_shader* fs) :
        fb(fb),
        vp(vp),
        vs(vs),
        fs(fs) {}
    
    void renderer::render_point(const vector<float>& v)
    {
        // run vertex shader
        const position pos = vs->run(v, vertex_attribs[0]);

        if (!pos.is_normalized()) { // clipping
            return;
        }

        // compute final framebuffer coordinates
        const unsigned fb_x = get_framebuf_x(pos.x);
        const unsigned fb_y = get_framebuf_y(pos.y);

        // run fragment shader
        const color fb_col = fs->run(vertex_attribs[0]);

        // write to framebuffer
        fb.write(fb_x, fb_y, fb_col, pos.z);
    }

    void renderer::render_line(const vector<float>& v1, const vector<float> v2)
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

        rasterize_line(x1, y1, pos1.z, x2, y2, pos2.z);
    }

    void renderer::render_triangle(const vector<float>& v1, const vector<float> v2, const vector<float> v3)
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

        rasterize_triangle(x1, y1, pos1.z, x2, y2, pos2.z, x3, y3, pos3.z);
    }

    void renderer::set_vs(const vertex_shader* vs) {
        this->vs = vs;
    }

    void renderer::set_fs(const fragment_shader* fs) {
        this->fs = fs;
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

    void renderer::rasterize_line(int x1, int y1, float d1, int x2, int y2, float d2)
    {
        // eliminate 2nd, 3rd, 6th, 7th octants (steep ones)
        bool steep = false;
        if (abs(y2 - y1) > abs(x2 - x1))
        {
            swap(x1, y1);
            swap(x2, y2);
            steep = true;
        }
        // eliminate 4th and 5th octants
        if (x1 > x2)
        {
            // swap vertices and all required data
            swap(x1, x2);
            swap(y1, y2);
            swap(d1, d2);
            swap(vertex_attribs[0], vertex_attribs[1]);
        }
        // eliminate 8th octant
        const int y_step = y2 > y1 ? 1 : -1;

        // end point differences
        const int dx = x2 - x1;
        const int dy = abs(y2 - y1);
        int error = 2 * dy - dx;

        init_interpolation(0, vertex_attribs[0], dx);
    
        // initial coordinates
        int x = x1;
        int y = y1;
        // final framebuffer coordinates
        const int& fb_x = steep ? y : x;
        const int& fb_y = steep ? x : y;

        while (x <= x2) // from x1 to x2
        {
            // interpolation -> fragment shader -> write to framebuffer
            interpolation(0, d1, vertex_attribs[0], d2, vertex_attribs[1], (x - x1) * interp_step[0]);
            color fb_col = fs->run(interp_attribs[0]);
            fb.write(fb_x, fb_y, fb_col, interp_depth[0]);

            if (error > 0)
            {
                y += y_step;
                error -= 2 * dx;
            }
            error += 2 * dy;

            x++;
        }
    }
    
    void renderer::rasterize_triangle(int x1, int y1, float d1, int x2, int y2, float d2, int x3, int y3, float d3)
    {
        // sort vertices by its y position (so that y1 <= y2 <= y3)
        if (y1 > y2)
        {
            swap(x1, x2);
            swap(y1, y2);
            swap(d1, d2);
            swap(vertex_attribs[0], vertex_attribs[1]);
        }
        if (y1 > y3)
        {
            swap(x1, x3);
            swap(y1, y3);
            swap(d1, d3);
            swap(vertex_attribs[0], vertex_attribs[2]);
        }
        if (y2 > y3)
        {
            swap(x2, x3);
            swap(y2, y3);
            swap(d2, d3);
            swap(vertex_attribs[1], vertex_attribs[2]);
        }

        // compute position differences
        const int dx12 = x2 - x1;
        const int dx13 = x3 - x1;
        const int dy12 = y2 - y1;
        const int dy13 = y3 - y1;

        // determine left and right edge
        const float slope12 = float(dx12) / dy12;
        const float slope13 = float(dx13) / dy13;
        const bool edge12_is_left = slope12 < slope13;

        // render top flat triangle (from bottom)
        int left_dx = edge12_is_left ? dx12 : dx13;
        int right_dx = edge12_is_left ? dx13 : dx12;
        int left_dy = edge12_is_left ? dy12 : dy13;
        int right_dy = edge12_is_left ? dy13 : dy12;

        int left_dx_sign = left_dx < 0 ? -1 : 1;
        int right_dx_sign = right_dx < 0 ? -1 : 1;
        left_dx = abs(left_dx);
        right_dx = abs(right_dx);

        int left_error = left_dy - left_dx;
        int right_error = right_dy - right_dx;
        int left_x = x1;
        int right_x = x1;

        for (int fb_y = y1; fb_y < y2; fb_y++)
        {
            while (left_error <= 0)
            {
                left_error += 2 * left_dy;
                left_x += left_dx_sign;
            }
            while (right_error <= 0)
            {
                right_error += 2 * right_dy;
                right_x += right_dx_sign;
            }

            for (int fb_x = left_x; fb_x < right_x; fb_x++) {
                fb.write(fb_x, fb_y, {1.f, 0.f, 0.f}, 0.f);
            }

            left_error -= 2 * left_dx;
            right_error -= 2 * right_dx;
        }

        // compute additional position differences
        const int dx23 = x3 - x2;
        const int dy23 = y3 - y2;

        // render bottom flat triangle (from top)
        if (edge12_is_left)
        {
            left_dx = dx23;
            left_dy = dy23;
            left_dx_sign = left_dx < 0 ? -1 : 1;
            left_dx = abs(left_dx);
        }
        else
        {
            right_dx = dx23;
            right_dy = dy23;
            right_dx_sign = right_dx < 0 ? -1 : 1;
            right_dx = abs(right_dx);
        }

        left_error = left_dy - left_dx;
        right_error = right_dy - right_dx;
        left_x = x3;
        right_x = x3;

        for (int fb_y = y3 - 1; fb_y >= y2; fb_y--)
        {
            while (left_error < 0)
            {
                left_error += 2 * left_dy;
                left_x -= left_dx_sign;
            }
            while (right_error < 0)
            {
                right_error += 2 * right_dy;
                right_x -= right_dx_sign;
            }

            for (int fb_x = left_x; fb_x < right_x; fb_x++) {
                fb.write(fb_x, fb_y, {0.f, 1.f, 0.f}, 0.f);
            }

            left_error -= 2 * left_dx;
            right_error -= 2 * right_dx;
        }
    }

    void renderer::init_interpolation(unsigned index, vector<float>& v1, unsigned step_count)    
    {
        assert(index <= 3);

        interp_step[index] = 1.f / step_count;
        interp_attribs[index].resize(v1.size());
    }

    void renderer::interpolation(unsigned index, float d1, vector<float>& v1, float d2, vector<float>& v2, float weight2)
    {
        assert(index <= 3);
        assert(v1.size() == interp_attribs[index].size() && v2.size() == interp_attribs[index].size());
        assert(weight2 >= 0.f && weight2 <= 1.f);

        float weight1 = 1.f - weight2;
        interp_depth[index] = weight1 * d1 + weight2 * d2; // depth interpolation

        for (unsigned i = 0; i < interp_attribs[index].size(); i++)
        {
            // interpolation of attributes
            interp_attribs[index][i] = weight1 * v1[i] + weight2 * v2[i];
        }
    }
}
