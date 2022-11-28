// https://github.com/dominiksalvet/cpurast

#include "framebuf.hpp"
#include <cstddef>
#include <vector>
#include <limits>

using std::vector;

namespace cr
{
    framebuf::framebuf(size_t width, size_t height) :
        width(width),
        height(height),
        clear_color(BLACK_COLOR),
        color_buf(height),
        test_depth(false)
    {
        for (size_t y; y < height; y++) {
            color_buf[y] = vector<color>(width);
        }
    }

    void framebuf::resize(size_t width, size_t height)
    {
        this->width = width;
        this->height = height;

        color_buf.resize(height);
        for (size_t y; y < height; y++) {
            color_buf[y].resize(width);
        }

        if (test_depth)
        {
            depth_buf.resize(height);
            for (size_t y; y < height; y++) {
                depth_buf[y].resize(width);
            }
        }
    }

    void framebuf::enable_depth_test()
    {
        depth_buf = depth_buf_t(height);
        for (size_t y; y < height; y++) {
            depth_buf[y] = vector<int16_t>(width);
        }

        test_depth = true;
    }

    void framebuf::clear(bool clear_color_buf, bool clear_depth_buf)
    {
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++)
            {
                if (clear_color_buf) {
                    color_buf[y][x] = clear_color;
                }
                if (test_depth && clear_depth_buf) {
                    depth_buf[y][x] = std::numeric_limits<int16_t>::min();
                }
            }
        }
    }

    void framebuf::write(size_t x, size_t y, int16_t depth, color color)
    {
        if (test_depth) {
            if (depth_buf[y][x] < depth)
            {
                color_buf[y][x] = color;
                depth_buf[y][x] = depth;
            }
        } else {
            color_buf[y][x] = color;
        }
    }

    size_t framebuf::get_width() {
        return this->width;
    }

    size_t framebuf::get_height() {
        return this->height;
    }
    
    const color_buf_t& framebuf::get_color_buf() {
        return color_buf;
    }
}
