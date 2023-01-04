// https://github.com/dominiksalvet/cpurast

#pragma once

namespace cr
{
    struct position
    {
        // check if position is located in the [-1, 1] space
        bool is_normalized() const
        {
            return x >= -1.f && x <= 1.f &&
                   y >= -1.f && y <= 1.f &&
                   z >= -1.f && z <= 1.f;
        }

        float x;
        float y;
        float z;
    };

    // using additive model for color representation
    // each color component has value of interval [0, 1]
    struct color
    {
        float r; // red
        float g; // green
        float b; // blue
    };

    struct viewport
    {
        unsigned x; // x viewport offset
        unsigned y; // y viewport offset
        unsigned width;
        unsigned height;
    };
}
