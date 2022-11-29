// https://github.com/dominiksalvet/cpurast

#include "context.hpp"

namespace cr
{
    context::context(size_t framebuf_width, size_t framebuf_height) :
        framebuf(framebuf_width, framebuf_height) {}
}
