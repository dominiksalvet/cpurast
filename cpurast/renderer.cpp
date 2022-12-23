// https://github.com/dominiksalvet/cpurast

#include "renderer.hpp"
#include <cassert>
#include <cmath>

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

        // if it is not a line, skip
        if (x1 == x2 && y1 == y2) {
            return;
        }

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

        // if it is not a triangle, skip
        if ((x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3) ||
            (x1 == x2 && x2 == x3) || (y1 == y2 && y2 == y3)) {
            return;
        }

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

        float w = vp.width;
        // position x=1 is mapped to width-1
        unsigned rel_x = x == 1.f ? w - 1 : ((x + 1) * w) / 2;
        return vp.x + rel_x;
    }

    unsigned renderer::get_framebuf_y(float y) const
    {
        assert(y >= -1.f && y <= 1.f);

        float h = vp.height;
        // position y=1 is mapped to height-1
        unsigned rel_y = y == 1.f ? h - 1 : ((y + 1) * h) / 2;
        return vp.y + rel_y;
    }

    void renderer::rasterize_line(int x1, int y1, float d1, int x2, int y2, float d2)
    {
        // eliminate 2nd, 3rd, 6th, 7th octants (steep ones)
        bool steep = false;
        if (std::abs(y2 - y1) > std::abs(x2 - x1))
        {
            std::swap(x1, y1);
            std::swap(x2, y2);
            steep = true;
        }
        // eliminate 4th and 5th octants
        if (x1 > x2)
        {
            // swap vertices and all required data
            std::swap(x1, x2);
            std::swap(y1, y2);
            std::swap(d1, d2);
            std::swap(vertex_attribs[0], vertex_attribs[1]);
        }
        // eliminate 8th octant
        const int y_step = y2 > y1 ? 1 : -1;

        // end point differences
        const int dx = x2 - x1;
        const int dy = std::abs(y2 - y1);
        int error = 2 * dy - dx;
    
        // initial coordinates
        int x = x1;
        int y = y1;
        // final framebuffer coordinates
        const int& fb_x = steep ? y : x;
        const int& fb_y = steep ? x : y;

        while (x <= x2) // from x1 to x2
        {
            // interpolation -> fragment shader -> write to framebuffer
            float fb_d = line_interpolation(d1, d2, x - x1, dx);
            color fb_col = fs->run(fragment_attribs);
            fb.write(fb_x, fb_y, fb_col, fb_d);

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
            std::swap(x1, x2);
            std::swap(y1, y2);
            std::swap(d1, d2);
            std::swap(vertex_attribs[0], vertex_attribs[1]);
        }
        if (y1 > y3)
        {
            std::swap(x1, x3);
            std::swap(y1, y3);
            std::swap(d1, d3);
            std::swap(vertex_attribs[0], vertex_attribs[2]);
        }
        if (y2 > y3)
        {
            std::swap(x2, x3);
            std::swap(y2, y3);
            std::swap(d2, d3);
            std::swap(vertex_attribs[1], vertex_attribs[2]);
        }

        // determine left and right edge
        const float slope12 = float(x2 - x1) / (y2 - y1);
        const float slope13 = float(x3 - x1) / (y3 - y1);
        const float slope23 = float(x3 - x2) / (y3 - y2);
        const bool edge12_is_left = slope12 < slope13;

        float left_slope = edge12_is_left ? slope12 : slope13;
        float right_slope = edge12_is_left ? slope13 : slope12;

        // render middle row only in appropriate flat rendering
        if (y1 == y2) {
            y2--;
        }

        // render flat top triangle (from bottom)
        float left_x = x1;
        float right_x = x1;
        for (int fb_y = y1; fb_y <= y2; fb_y++)
        {
            for (int fb_x = std::round(left_x); fb_x <= std::round(right_x); fb_x++) {
                fb.write(fb_x, fb_y, {1.f, 1.f, 1.f}, 0.f);
            }
            left_x += left_slope;
            right_x += right_slope;
        }

        // render bottom flat triangle (from top)
        if (edge12_is_left) {
            left_slope = slope23;
        } else {
            right_slope = slope23;
        }

        left_x = x3;
        right_x = x3;
        for (int fb_y = y3; fb_y > y2; fb_y--)
        {
            for (int fb_x = std::round(left_x); fb_x <= std::round(right_x); fb_x++) {
                fb.write(fb_x, fb_y, {1.f, 1.f, 1.f}, 0.f);
            }
            left_x -= left_slope;
            right_x -= right_slope;
        }
    }

    float renderer::line_interpolation(float d1, float d2, unsigned cur, unsigned total)
    {
        assert(vertex_attribs[0].size() == vertex_attribs[1].size());

        float progress = float(cur) / total;
        float d = d1 * (1.f - progress) + d2 * progress; // depth interpolation

        fragment_attribs.resize(vertex_attribs[0].size());
        for (unsigned i = 0; i < fragment_attribs.size(); i++)
        {
            // fragment attributes interpolation
            fragment_attribs[i] = vertex_attribs[0][i] * (1.f - progress) + vertex_attribs[1][i] * progress;
        }

        return d;
    }
}
