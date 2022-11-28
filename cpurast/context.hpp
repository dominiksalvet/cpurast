// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

namespace cr
{
    // index of default framebuffer used for display rendering
    constexpr size_t DEFAULT_FRAMEBUF = 0;

    class context
    {
    public:
        // constructor with default framebuffer width and height
        context(size_t framebuf_width, size_t framebuf_height);

    private:
        shared_ptr<framebuf> active_framebuf;

        vector<shared_ptr<framebuf>> framebufs;
    };
}
