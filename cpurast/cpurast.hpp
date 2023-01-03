// https://github.com/dominiksalvet/cpurast

#pragma once

#include "framebuf.hpp"
#include "canvas.hpp"
#include <memory>
#include "shader.hpp"
#include "renderer.hpp"
#include "default_shader.hpp"

using std::shared_ptr;
using std::make_shared;

namespace cr
{
    class context
    {
    public: // cpurast API
        // create cpurast context with default vertex and fragment shaders
        context(cr::canvas& canvas, unsigned canvas_w, unsigned canvas_h);

        // draw framebuffer to the canvas
        void update_canvas() const;
        // change active canvas pointer (foreign ownership)
        void bind_canvas(cr::canvas& canvas);

        // change the resolution of the framebuffer
        void resize_framebuf(unsigned new_width, unsigned new_height);
        // clear individual buffers of the framebuffer
        void clear_framebuf(bool clear_color, bool clear_depth);
        // set clear color of framebuffer's color buffer
        void set_clear_color(float r, float g, float b);
        // normalized device coordinates are in the given frame of the framebuffer
        void set_viewport(unsigned x, unsigned y, unsigned width, unsigned height);
        // enable/disable depth test for framebuffer
        void enable_depth_test();
        void disable_depth_test();
        // enable interpolation of vertex attributes
        void enable_interpolation();
        // disable interpolation, uses first vertex attributes for all fragments
        void disable_interpolation();

        // drawing of primitives (v - vertex attributes)
        void draw_point(const vector<float>& v);
        void draw_line(const vector<float>& v1, const vector<float>& v2);
        void draw_triangle(const vector<float>& v1, const vector<float>& v2, const vector<float>& v3);

        // change active vertex shader program (shared ownership)
        void bind_vertex_shader(const shared_ptr<const vertex_shader>& v_shader);
        // change active fragment shader program (shared ownership)
        void bind_fragment_shader(const shared_ptr<const fragment_shader>& f_shader);

    private:
        cr::canvas* canvas; // canvas for drawing pixels
        cr::framebuf framebuf; // framebuffer for rendering

        shared_ptr<const vertex_shader> v_shader = make_shared<default_vs>(); // active vertex shader
        shared_ptr<const fragment_shader> f_shader = make_shared<default_fs>(); // active fragment shader
        cr::renderer renderer; // graphics renderer
    };
}
