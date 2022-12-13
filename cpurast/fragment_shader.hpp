// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>
#include "color.hpp"

using std::vector;

namespace cr
{
    // abstract class for fragment shader representation
    class fragment_shader
    {
    public:
        virtual ~fragment_shader() = default;

        // run per-fragment operation
        virtual color run(const vector<float>& f) = 0;

        void set_uniforms(const vector<float>& uniforms) {
            this->uniforms = std::move(uniforms);
        }

    protected:
        vector<float> uniforms;
    };
}
