// https://github.com/dominiksalvet/cpurast

#include "framebuf.hpp"
#include <cassert>

namespace cr
{
    framebuf::framebuf(unsigned width, unsigned height) :
        width(width),
        height(height),
        color_buf(width * height) {}

    void framebuf::resize(unsigned new_width, unsigned new_height)
    {
        color_buf.resize(new_width * new_height);

        if (depth_test_enabled) {
            depth_buf.resize(new_width * new_height);
        }

        width = new_width;
        height = new_height;
    }

    void framebuf::enable_depth_test()
    {
        if (depth_test_enabled) {
            return;
        }

        depth_buf.resize(width * height);
        depth_test_enabled = true;
    }
    
    void framebuf::disable_depth_test()
    {
        if (!depth_test_enabled) {
            return;
        }

        depth_test_enabled = false;
        depth_buf.clear();
    }

    void framebuf::clear(bool clear_color_buf, bool clear_depth_buf)
    {
        const unsigned total_size = width * height;

        for (unsigned i = 0; i < total_size; i++)
        {
            if (clear_color_buf) {
                color_buf[i] = clear_color;
            }
            if (depth_test_enabled && clear_depth_buf) {
                depth_buf[i] = -1.f;
            }
        }
    }

    unsigned framebuf::get_index(unsigned x, unsigned y) const
    {
        assert(x < width && y < height);

        // the bottom row has y value of 0
        return (height - y - 1) * width + x;
    }

    bool framebuf::depth_test(unsigned index, float depth)
    {
        if (depth_test_enabled)
        {
            assert(depth >= -1.f && depth <= 1.f);

            bool depth_test_passed = depth > depth_buf[index];
            if (depth_test_passed) {
                depth_buf[index] = depth;
            }
            return depth_test_passed;
        }

        return true; // no checks when depth test is disabled
    }

    void framebuf::write(unsigned index, cr::color color) {
        color_buf[index] = color;
    }

    unsigned framebuf::get_width() const {
        return width;
    }

    unsigned framebuf::get_height() const {
        return height;
    }

    void framebuf::set_clear_color(color clear_color) {
        this->clear_color = clear_color;
    }

    const vector<color>& framebuf::get_color_buf() const {
        return color_buf;
    }
}
