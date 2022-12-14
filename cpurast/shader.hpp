// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>
#include <array>

using std::vector;
using std::array;

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
        // arguments: input attributes, output position [x, y, z], output attributes (empty on call)
        virtual void run(const vector<float>& in_a, array<float, 3>& out_p, vector<float>& out_a) const = 0;
    };

    // abstract class for fragment shader representation
    class fragment_shader : public shader
    {
    public:
        virtual ~fragment_shader() = default;

        // run per-fragment operation with given fragment attributes
        // arguments: input attributes, output normalized color [r, g, b]
        virtual void run(const vector<float>& in_a, array<float, 3>& out_c) const = 0;
    };
}
