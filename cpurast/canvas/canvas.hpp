// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include <exception>
#include <string>

namespace cr
{
    // abstract class for displaying graphics on a canvas (part of screen)
    class canvas
    {
    public:
        virtual ~canvas() = default;
        // canvas resolution and color buffer resolution must be the same
        virtual void draw(const color_buf_t& color_buf, size_t width, size_t height) = 0;
    };

    // bad canvas to draw on exception (should be used in canvas constructors)
    class bad_canvas : public std::exception
    {
    public:
        bad_canvas(const std::string& msg) : msg(msg) {}

        virtual const char* what() const throw() override {
            return msg.c_str();
        }

    private:
        const std::string msg;
    };
}
