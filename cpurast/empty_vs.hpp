// https://github.com/dominiksalvet/cpurast

#pragma once

#include "vertex_shader.hpp"

namespace cr
{
    // empty vertex shader
    class empty_vs : public vertex_shader
    {
    public:
        empty_vs() :
            vertex_shader({}) {}

        const cr::vertex& run(const cr::vertex& v) override {
            return v; // forward input to output
        }
    };
}
