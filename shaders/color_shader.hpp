// https://github.com/dominiksalvet/cpurast

#pragma once

#include "shader.hpp"
#include <cassert>

class color_vs : public cr::vertex_shader
{
public:
    void run(const vector<float>& in_a, array<float, 3>& out_p, vector<float>& out_a) const override
    {
        assert(in_a.size() >= 6);

        out_p[0] = in_a[0]; // x
        out_p[1] = in_a[1]; // y
        out_p[2] = in_a[2]; // z

        out_a.resize(3);
        out_a[0] = in_a[3]; // r
        out_a[1] = in_a[4]; // g
        out_a[2] = in_a[5]; // b
    }
};

class color_fs : public cr::fragment_shader
{
public:
    void run(const vector<float>& in_a, array<float, 3>& out_c) const override
    {
        assert(in_a.size() >= 3);

        out_c[0] = in_a[0]; // r
        out_c[1] = in_a[1]; // g
        out_c[2] = in_a[2]; // b
    }
};
