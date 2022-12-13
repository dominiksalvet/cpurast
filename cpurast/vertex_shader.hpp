// https://github.com/dominiksalvet/cpurast

#pragma once

#include "vertex.hpp"
#include <vector>

using std::vector;

namespace cr
{
    // abstract class for vertex shader representation
    class vertex_shader
    {
    public:
        vertex_shader(const vector<float>& uniforms) {
            set_uniforms(uniforms);
        }
        virtual ~vertex_shader() = default;

        // run per-vertex operation
        virtual const vertex& run(const vertex& v) = 0;

        void set_uniforms(const vector<float>& uniforms) {
            this->uniforms = std::move(uniforms);
        }

    protected:
        vector<float> uniforms;
    };
}