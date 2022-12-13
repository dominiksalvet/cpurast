// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>

namespace cr
{
    struct vertex
    {
        float x;
        float y;
        float z;
        std::vector<float> attribs; // optional extra attributes
    };
}
