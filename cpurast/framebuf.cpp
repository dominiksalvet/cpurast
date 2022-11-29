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
        for (size_t y = 0; y < height; y++) {
            color_buf[y] = vector<color>(width);
        }
    }

    void framebuf::resize(size_t new_width, size_t new_height)
    {
        resize_buf(color_buf, new_width, new_height);

        if (test_depth) {
            resize_buf(depth_buf, new_width, new_height);
        }

        width = new_width;
        height = new_height;
    }

    void framebuf::enable_depth_test()
    {
        if (test_depth) {
            return;
        }

        depth_buf = depth_buf_t(height);
        for (size_t y = 0; y < height; y++) {
            depth_buf[y] = vector<float>(width);
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
                    depth_buf[y][x] = 1.f;
                }
            }
        }
    }

    void framebuf::write(size_t x, size_t y, color color, float depth)
    {
        if (test_depth) {
            if (depth < depth_buf[y][x])
            {
                color_buf[y][x] = color;
                depth_buf[y][x] = depth;
            }
        } else {
            color_buf[y][x] = color;
        }
    }

    template <typename T>
    void framebuf::resize_buf(vector<vector<T>>& buf, size_t new_width, size_t new_height) const
    {
        buf.resize(new_height);
        for (size_t y = 0; y < new_height; y++) {
            if (y < height) {
                buf[y].resize(new_width); // resize existing vectors
            } else {
                buf[y] = vector<T>(new_width); // create new vectors
            }
        }
    }
}
