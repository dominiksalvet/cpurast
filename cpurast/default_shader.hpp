// https://github.com/dominiksalvet/cpurast

#pragma once

#include "shader.hpp"
#include <cassert>

namespace cr
{
    // default vertex shader
    class default_vs : public vertex_shader
    {
    public:
        position run(const vector<float>& in, vector<float>& out) const override
        {
            assert(in.size() >= 3);

            // assuming that the first three attributes represent vertex position
            // performs no vertex transformation
            return {in[0], in[1], in[2]}; // x, y, z
        }
    };

    // default fragment shader
    class default_fs : public fragment_shader
    {
    public:
        color run(const vector<float>& in) const override
        {
            // ignore input attributes and use white color for all fragments
            return {1.f, 1.f, 1.f}; // r, g, b
        }
    };
}
