// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>
#include "color.hpp"

using std::vector;

namespace cr
{
    class framebuf
    {
    public:
        framebuf(unsigned width, unsigned height);

        void resize(unsigned new_width, unsigned new_height);
        void enable_depth_test();
        void clear(bool clear_color_buf, bool clear_depth_buf);

        // the origin of the coordinate system is placed at the left bottom
        // higher depth value means it is closer to the viewport
        // if depth test is disabled, depth value is ignored
        void write(unsigned x, unsigned y, cr::color color, float depth);

        unsigned get_width() const;
        unsigned get_height() const;
        void set_clear_color(color clear_color);
        const vector<color>& get_color_buf() const;

    private:
        unsigned width;
        unsigned height;

        color clear_color; // color used for clearing color buffer
        vector<color> color_buf; // color buffer representation

        bool test_depth; // depth test enable flag
        vector<float> depth_buf; // depth buffer of values [-1, 1]
    };
}
