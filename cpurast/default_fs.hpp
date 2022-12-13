// https://github.com/dominiksalvet/cpurast

#pragma once

#include "fragment_shader.hpp"

namespace cr
{
    // default fragment shader
    class default_fs : public fragment_shader
    {
    public:
        color run(const vector<float>& f) override {
            return WHITE_COLOR; // all fragments are white
        }
    };
}
