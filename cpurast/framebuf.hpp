// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>
#include <cstddef>
#include "color.hpp"

using std::vector;

namespace cr
{
    class framebuf
    {
    public:
        framebuf(size_t width, size_t height);

        void resize(size_t new_width, size_t new_height);
        void enable_depth_test();
        void clear(bool clear_color_buf, bool clear_depth_buf);
        // if depth test is disabled, depth value is ignored
        // lower depth value means it is closer to the viewport
        void write(size_t x, size_t y, cr::color color, float depth);

        size_t get_width() const;
        size_t get_height() const;
        void set_clear_color(color clear_color);
        const vector<color>& get_color_buf() const;

    private:
        size_t width;
        size_t height;

        color clear_color; // color used for clearing color buffer
        vector<color> color_buf; // color buffer representation

        bool test_depth; // depth test enable flag
        vector<float> depth_buf; // depth buffer of values [0, 1]
    };
}
