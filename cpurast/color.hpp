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

    constexpr color BLACK_COLOR = { 0.f, 0.f, 0.f };
    constexpr color WHITE_COLOR = { 1.f, 1.f, 1.f };
    constexpr color RED_COLOR   = { 1.f, 0.f, 0.f };
    constexpr color GREEN_COLOR = { 0.f, 1.f, 0.f };
    constexpr color BLUE_COLOR  = { 0.f, 0.f, 1.f };
}
