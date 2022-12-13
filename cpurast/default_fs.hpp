// https://github.com/dominiksalvet/cpurast

#pragma once

#include "shader.hpp"

namespace cr
{
    // default fragment shader
    class default_fs : public fragment_shader
    {
    public:
        void run(const vector<float>& in_a, array<float, 3>& out_c) override
        {
            // ignore input attributes and use white color for all fragments
            out_c[0] = 1.f; // r
            out_c[1] = 1.f; // g
            out_c[2] = 1.f; // b
        }
    };
}
