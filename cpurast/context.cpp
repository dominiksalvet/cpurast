// https://github.com/dominiksalvet/cpurast

#include "context.hpp"

namespace cr
{
    context::context(cr::canvas& canvas) :
        canvas(canvas),
        framebuf(canvas.get_width(), canvas.get_height()) {}
}
