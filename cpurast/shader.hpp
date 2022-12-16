// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>
#include "position.hpp"
#include "color.hpp"

using std::vector;

namespace cr
{
    // abstract class for shader representation
    class shader
    {
    public:
        virtual ~shader() = default;

        void set_uniforms(const vector<float>& uniforms) {
            this->uniforms = std::move(uniforms);
        }

    protected:
        shader() = default; // no instances allowed

        vector<float> uniforms;
    };

    // abstract class for vertex shader representation
    class vertex_shader : public shader
    {
    public:
        virtual ~vertex_shader() = default;

        // run per-vertex operation with given vertex attributes
        // returns: output position, arguments: input attributes, output attributes (resize as you require)
        virtual position run(const vector<float>& in, vector<float>& out) const = 0;
    };

    // abstract class for fragment shader representation
    class fragment_shader : public shader
    {
    public:
        virtual ~fragment_shader() = default;

        // run per-fragment operation with given fragment attributes
        // returns: output normalized color, arguments: input attributes
        virtual color run(const vector<float>& in) const = 0;
    };
}
