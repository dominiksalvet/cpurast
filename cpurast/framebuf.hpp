// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>
#include <cstddef>
#include "color.hpp"

using std::vector;

namespace cr
{
    // color and depth buffer reprezentation [y][x]
    typedef vector<vector<color>> color_buf_t;
    typedef vector<vector<int16_t>> depth_buf_t;

    class framebuf
    {
    public:
        framebuf(size_t width, size_t height);
        void resize(size_t width, size_t height);
        void enable_depth_test();
        void clear(bool clear_color_buf, bool clear_depth_buf);
        // if depth test is disabled, depth value is ignored
        void write(size_t x, size_t y, int16_t depth, color color);

        size_t get_width();
        size_t get_height();
        const color_buf_t& get_color_buf();

        color clear_color;
    
    private:
        size_t width;
        size_t height;

        color_buf_t color_buf;

        bool test_depth; // enable/disable depth test
        depth_buf_t depth_buf;
    };
}
