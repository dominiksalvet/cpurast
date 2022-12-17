// https://github.com/dominiksalvet/cpurast

#pragma once

namespace cr
{
    struct position
    {
        // check if position is located in the [-1, 1] space
        bool is_normalized()
        {
            return x >= -1.f && x <= 1.f &&
                   y >= -1.f && y <= 1.f &&
                   z >= -1.f && z <= 1.f;
        }

        float x;
        float y;
        float z;
    };
}
