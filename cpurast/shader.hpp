// https://github.com/dominiksalvet/cpurast

#pragma once

#include "util.hpp"
#include <vector>
#include <cassert>

using std::vector;

namespace cr
{
    // abstract class for shader representation
    class shader
    {
    public:
        virtual ~shader() = default;

        void set_uniforms(const vector<float>& uniforms) {
            this->uniforms = uniforms; // copy uniforms vector
        }

        void set_uniforms(vector<float>&& uniforms) noexcept {
            this->uniforms = std::move(uniforms); // steal uniforms vector
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
