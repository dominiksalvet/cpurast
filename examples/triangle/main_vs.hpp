// https://github.com/dominiksalvet/cpurast

#pragma once

#include "cpurast.hpp"

class main_vs : public cr::vertex_shader
{
public:
    main_vs(const vector<float>& uniforms) :
        vertex_shader(uniforms) {}

    const cr::vertex& run(const cr::vertex& v) override
    {
        // todo: add vertex shader code
        return v;
    }
};
