// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>

namespace cr
{
    // first three items must be vertex positions x, y, z
    // other items are extra attributes (optional)
    using vertex = std::vector<float>;
}
