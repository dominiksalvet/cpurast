// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include "canvas.hpp"
#include "viewport.hpp"
#include <memory>
#include "shader.hpp"

using std::shared_ptr;

namespace cr
{
    class context
    {
    public: // cpurast API
        context(cr::canvas* canvas, size_t canvas_w, size_t canvas_h);

        // draw framebuffer to the canvas
        void update_canvas() const;
        // change active canvas pointer (pointer due to foreign ownership)
        void bind_canvas(cr::canvas* canvas);

        // change the resolution of the framebuffer
        void resize_framebuf(size_t new_width, size_t new_height);
        // enable depth test for framebuffer
        void enable_depth_test();
        // set clear color of framebuffer's color buffer
        void set_clear_color(float r, float g, float b);
        // clear individual buffers of the framebuffer
        void clear_framebuf(bool clear_color, bool clear_depth);

        // normalized device coordinates are in the given frame of the framebuffer
        void set_viewport(size_t x, size_t y, size_t width, size_t height);

        // change active vertex shader program
        void bind_vertex_shader(const shared_ptr<const vertex_shader>& vs);
        // change active fragment shader program
        void bind_fragment_shader(const shared_ptr<const fragment_shader>& fs);

    private:
        // transform normalized coordinates [0, 1] to framebuffer coordinates
        size_t get_framebuf_x(float x) const;
        size_t get_framebuf_y(float y) const;

        cr::canvas* canvas; // canvas for drawing pixels

        cr::framebuf framebuf; // framebuffer for rendering
        cr::viewport viewport; // current viewport properties

        shared_ptr<const vertex_shader> vs; // active vertex shader
        shared_ptr<const fragment_shader> fs; // active fragment shader
    };
}
