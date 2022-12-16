// https://github.com/dominiksalvet/cpurast

#pragma once

#include "shader.hpp"
#include <cassert>

class color_vs : public cr::vertex_shader
{
public:
    cr::position run(const vector<float>& in, vector<float>& out) const override
    {
        assert(in.size() >= 6);

        out.resize(3);
        out[0] = in[3]; // r
        out[1] = in[4]; // g
        out[2] = in[5]; // b

        return {in[0], in[1], in[2]}; // x, y, z
    }
};

class color_fs : public cr::fragment_shader
{
public:
    cr::color run(const vector<float>& in) const override
    {
        assert(in.size() >= 3);

        return {in[0], in[1], in[2]}; // r, g, b
    }
};
