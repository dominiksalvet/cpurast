// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>
#include <cstddef>
#include "color.hpp"

using std::vector;

namespace cr
{
    // color buffer representation [y][x]
    using color_buf_t = vector<vector<color>>;
    // depth buffer of values [-1, 1]
    using depth_buf_t = vector<vector<float>>;

    class framebuf
    {
    public:
        framebuf(size_t width, size_t height);

        void resize(size_t new_width, size_t new_height);
        void enable_depth_test();
        void clear(bool clear_color_buf, bool clear_depth_buf);
        // if depth test is disabled, depth value is ignored
        // lower depth means it is closer to the viewport
        void write(size_t x, size_t y, color color, float depth);

        size_t get_width();
        size_t get_height();

    private:
        template <typename T>
        void resize_buf(vector<vector<T>>& buf, size_t new_width, size_t new_height) const;
    
    public:
        color clear_color;

    private:
        size_t width;
        size_t height;

        color_buf_t color_buf;

        bool test_depth; // depth test enable flag
        depth_buf_t depth_buf;
    };
}
