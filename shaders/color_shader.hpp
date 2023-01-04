// https://github.com/dominiksalvet/cpurast

#pragma once

#include "shader.hpp"

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
        assert(in[0] >= 0.f && in[0] <= 1.f);
        assert(in[1] >= 0.f && in[1] <= 1.f);
        assert(in[2] >= 0.f && in[2] <= 1.f);

        return {in[0], in[1], in[2]}; // r, g, b
    }
};
