// https://github.com/dominiksalvet/cpurast

#include "renderer.hpp"
#include <cassert>
#include <cstdlib>

namespace cr
{
    renderer::renderer(framebuf& fb, viewport& vp, const vertex_shader* vs, const fragment_shader* fs) :
        fb(fb),
        vp(vp),
        vs(vs),
        fs(fs) {}
    
    void renderer::render_point(const vector<float>& v)
    {
        position pos = vs->run(v, vertex_attribs[0]); // run vertex shader

        if (!pos.is_normalized()) { // clipping
            return;
        }

        // compute final framebuffer coordinates
        unsigned int fb_x = get_framebuf_x(pos.x);
        unsigned int fb_y = get_framebuf_y(pos.y);

        color fb_col = fs->run(vertex_attribs[0]); // run fragment shader

        // write to framebuffer
        fb.write(fb_x, fb_y, fb_col, pos.z);
    }

    void renderer::render_line(const vector<float>& v1, const vector<float> v2)
    {
        // run vertex shader
        position pos1 = vs->run(v1, vertex_attribs[0]);
        position pos2 = vs->run(v2, vertex_attribs[1]);

        if (!pos1.is_normalized() || !pos2.is_normalized()) { // simple clipping
            return;
        }

        // compute endpoint framebuffer coordinates
        int x1 = get_framebuf_x(pos1.x);
        int y1 = get_framebuf_y(pos1.y);
        int x2 = get_framebuf_x(pos2.x);
        int y2 = get_framebuf_y(pos2.y);

        // if it is not a line, skip
        if (x1 == x2 && y1 == y2) {
            return;
        }

        // rasterization (Bresenham's line algorithm)
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
            std::swap(pos1.z, pos2.z);
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
            float fb_z = line_interpolation(pos1.z, pos2.z, x - x1, dx);
            color fb_col = fs->run(fragment_attribs);
            fb.write(fb_x, fb_y, fb_col, fb_z);

            if (error > 0)
            {
                y += y_step;
                error -= 2 * dx;
            }
            error += 2 * dy;

            x++;
        }
    }

    void renderer::render_triangle(const vector<float>& v1, const vector<float> v2, const vector<float> v3)
    {
        render_line(v1, v2);
        render_line(v2, v3);
        render_line(v3, v1);
    }

    void renderer::set_vs(const vertex_shader* vs) {
        this->vs = vs;
    }

    void renderer::set_fs(const fragment_shader* fs) {
        this->fs = fs;
    }

    unsigned int renderer::get_framebuf_x(float x) const
    {
        assert(x >= -1.f && x <= 1.f);

        float w = vp.width;
        // each pixel is addressable by its center
        return (x * (w - 1) + w) / 2 + vp.x;
    }

    unsigned int renderer::get_framebuf_y(float y) const
    {
        assert(y >= -1.f && y <= 1.f);

        float h = vp.height;
        // each pixel is addressable by its center
        return (y * (h - 1) + h) / 2 + vp.y;
    }

    float renderer::line_interpolation(float d1, float d2, unsigned int cur, unsigned int total)
    {
        assert(vertex_attribs[0].size() == vertex_attribs[1].size());

        float progress = float(cur) / total;
        float d = d1 * (1.f - progress) + d2 * progress; // depth interpolation

        fragment_attribs.resize(vertex_attribs[0].size());
        for (unsigned int i = 0; i < fragment_attribs.size(); i++)
        {
            // fragment attributes interpolation
            fragment_attribs[i] = vertex_attribs[0][i] * (1.f - progress) + vertex_attribs[1][i] * progress;
        }

        return d;
    }
}
