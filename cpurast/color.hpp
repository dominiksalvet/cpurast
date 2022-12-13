// https://github.com/dominiksalvet/cpurast

#pragma once

namespace cr
{
    // using additive model for color representation
    // each color component has value of interval [0, 1]
    struct color
    {
        float r; // red
        float g; // green
        float b; // blue
    };
}
