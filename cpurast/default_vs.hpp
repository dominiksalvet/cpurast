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
        void run(const vector<float>& in_a, array<float, 3>& out_p, vector<float>& out_a) override
        {
            assert(in_a.size() >= 3);

            // assuming that the first three attributes represent vertex position
            // performs no vertex transformation
            out_p[0] = in_a[0]; // x
            out_p[1] = in_a[1]; // y
            out_p[2] = in_a[2]; // z
        }
    };
}
