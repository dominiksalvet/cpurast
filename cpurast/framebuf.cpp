// https://github.com/dominiksalvet/cpurast

#include "framebuf.hpp"
#include <cassert>

namespace cr
{
    framebuf::framebuf(size_t width, size_t height) :
        width(width),
        height(height),
        clear_color(BLACK_COLOR), // default clear color
        color_buf(width * height),
        test_depth(false) {}

    void framebuf::resize(size_t new_width, size_t new_height)
    {
        color_buf.resize(new_width * new_height);

        if (test_depth) {
            depth_buf.resize(new_width * new_height);
        }

        width = new_width;
        height = new_height;
    }

    void framebuf::enable_depth_test()
    {
        if (test_depth) {
            return;
        }

        depth_buf.resize(width * height);
        test_depth = true;
    }

    void framebuf::clear(bool clear_color_buf, bool clear_depth_buf)
    {
        const size_t total_size = width * height;

        for (size_t i = 0; i < total_size; i++)
        {
            if (clear_color_buf) {
                color_buf[i] = clear_color;
            }
            if (clear_depth_buf) {
                depth_buf[i] = 1.f;
            }
        }
    }

    void framebuf::write(size_t x, size_t y, cr::color color, float depth)
    {
        assert(x < width && y < height);

        const size_t cur_index = y * width + x;

        if (test_depth) {
            if (depth < depth_buf[cur_index])
            {
                color_buf[cur_index] = color;
                depth_buf[cur_index] = depth;
            }
        } else {
            color_buf[cur_index] = color;
        }
    }

    size_t framebuf::get_width() {
        return width;
    }

    size_t framebuf::get_height() {
        return height;
    }

    void framebuf::set_clear_color(color clear_color)
    {
        assert(clear_color.r >= 0.f && clear_color.r <= 1.f);
        assert(clear_color.g >= 0.f && clear_color.g <= 1.f);
        assert(clear_color.b >= 0.f && clear_color.b <= 1.f);

        this->clear_color = clear_color;
    }

    const vector<color>& framebuf::get_color_buf() {
        return color_buf;
    }
}
