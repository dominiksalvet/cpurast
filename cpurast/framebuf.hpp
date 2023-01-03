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
        void disable_depth_test();
        void clear(bool clear_color_buf, bool clear_depth_buf);

        // returns single index to framebuffer based on given x and y coordinates
        // the origin of the framebuffer coordinate system is placed at the left bottom
        unsigned get_index(unsigned x, unsigned y) const;

        // checks whether given depth value is higher (closer to the viewport) than depth buffer value
        // if so, updates depth buffer and returns success, otherwise fails
        // if depth test is disabled, depth value is ignored and always returns success
        bool depth_test(unsigned index, float depth);
        // this function should be called only after a successful depth test
        void write(unsigned index, cr::color color);

        unsigned get_width() const;
        unsigned get_height() const;
        void set_clear_color(color clear_color);
        const vector<color>& get_color_buf() const;

    private:
        unsigned width;
        unsigned height;

        color clear_color{0.f, 0.f, 0.f}; // color used for clearing color buffer
        vector<color> color_buf; // color buffer representation

        bool depth_test_enabled = false; // depth test enable flag
        vector<float> depth_buf; // depth buffer of values [-1, 1]
    };
}
