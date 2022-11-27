// https://github.com/dominiksalvet/cpurast

#pragma once

#include <cstdint>

namespace cr
{
    // using additive color model
    struct color
    {
        uint8_t r; // red
        uint8_t g; // green
        uint8_t b; // blue
    };

    constexpr color BLACK_COLOR = {0,     0,   0};
    constexpr color WHITE_COLOR = {255, 255, 255};
    constexpr color RED_COLOR   = {255,   0,   0};
    constexpr color GREEN_COLOR = {0,   255,   0};
    constexpr color BLUE_COLOR  = {0,     0, 255};
}
