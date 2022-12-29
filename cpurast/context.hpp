// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include "canvas.hpp"
#include "viewport.hpp"
#include <memory>
#include "shader.hpp"
#include "renderer.hpp"

using std::shared_ptr;

namespace cr
{
    class context
    {
    public: // cpurast API
        context(cr::canvas* canvas, unsigned canvas_w, unsigned canvas_h);

        // draw framebuffer to the canvas
        void update_canvas() const;
        // change active canvas pointer (pointer due to foreign ownership)
        void bind_canvas(cr::canvas* canvas);

        // change the resolution of the framebuffer
        void resize_framebuf(unsigned new_width, unsigned new_height);
        // enable depth test for framebuffer
        void enable_depth_test();
        // set clear color of framebuffer's color buffer
        void set_clear_color(float r, float g, float b);
        // clear individual buffers of the framebuffer
        void clear_framebuf(bool clear_color, bool clear_depth);

        // normalized device coordinates are in the given frame of the framebuffer
        void set_viewport(unsigned x, unsigned y, unsigned width, unsigned height);

        // change active vertex shader program
        void bind_vertex_shader(const shared_ptr<const vertex_shader>& v_shader);
        // change active fragment shader program
        void bind_fragment_shader(const shared_ptr<const fragment_shader>& f_shader);

        // drawing of primitives (v - vertex attributes)
        void draw_point(const vector<float>& v);
        void draw_line(const vector<float>& v1, const vector<float>& v2);
        void draw_triangle(const vector<float>& v1, const vector<float>& v2, const vector<float>& v3);

    private:
        cr::canvas* canvas; // canvas for drawing pixels

        cr::framebuf framebuf; // framebuffer for rendering
        cr::viewport viewport; // current viewport properties

        shared_ptr<const vertex_shader> v_shader; // active vertex shader
        shared_ptr<const fragment_shader> f_shader; // active fragment shader

        cr::renderer renderer; // graphics renderer
    };
}
