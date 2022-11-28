// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"

namespace cr
{
    class context
    {
    public:
        context(size_t framebuf_width, size_t framebuf_height);

    private:
        cr::framebuf framebuf;
    };
}
