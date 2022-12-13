// https://github.com/dominiksalvet/cpurast

#pragma once

#include <vector>

using std::vector;

namespace cr
{
    // first three items must be vertex positions x, y, z
    // other items are extra attributes (optional)
    using vertex = vector<float>;
}
