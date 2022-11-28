// https://github.com/dominiksalvet/cpurast

#include "context.hpp"
#include <memory>

namespace cr
{
    context::context(size_t framebuf_width, size_t framebuf_height)
    {
        framebufs.emplace_back(new framebuf(framebuf_width, framebuf_height));
        active_framebuf = framebufs[DEFAULT_FRAMEBUF];
    }
}
