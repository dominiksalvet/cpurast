// https://github.com/dominiksalvet/cpurast

#pragma once

#include "vertex_shader.hpp"

namespace cr
{
    // default vertex shader
    class default_vs : public vertex_shader
    {
    public:
        vertex run(const vertex& v) override {
            return v; // forward input to output
        }
    };
}
