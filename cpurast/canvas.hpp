// https://github.com/dominiksalvet/cpurast

#pragma once

#include "util.hpp"
#include <vector>

namespace cr
{
    // interface for displaying graphics on a canvas (e.g., content of window)
    class canvas
    {
    public:
        virtual ~canvas() = default;

        // canvas resolution and color buffer resolution must be the same
        virtual void draw(const std::vector<color>& color_buf, unsigned width, unsigned height) = 0;
    };
}
