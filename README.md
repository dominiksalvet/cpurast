# CPU Rasterizer

The cpurast is a software rasterizer written from scratch. Basically, it is a very simple and limited imitation of a graphics library (such as OpenGL), yet it performs all graphical computations on the processor. This approach is much slower than using a graphics processor, but it is more flexible since it has no additional driver and hardware requirements. Surprisingly, cpurast comes with a set of advanced [features](#features).

This project was created during my master's studies. I chose this assignment because I wanted to get an idea of what could be inside a real graphics processor so that it supports the functions of graphics libraries. When I started, I had just a little experience with computer graphics, so I had to study a lot. Feel free to take a look at the [used sources](#used-sources) from which I have gained my knowledge.

## Features

* Vertex and fragment shaders
* Z-buffering support
* Viewport rendering
* Normalized coordinates
* Normalized colors
* Cross platform, minimal dependencies

## How to Run Examples

Requirements to run examples:

* [SDL2 library](https://www.libsdl.org/)
* [CMake tools](https://cmake.org/)
* A C++ compiler

Building examples that use **cpurast**:

```
cd cpurast
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" ..
make
```

Running a **triangle** example after building:

```
./examples/triangle/triangle
```

## How to Use as a Library

Minimum requirements to use the library:

* A C++ compiler

What may be useful:

* Delivered CMake build system
* Delivered examples of use

> It is suggested to start with an existing example, copy it to a new example directory, and start customizing it. Later, after some experience with using and building cpurast, the created program may be used as the foundation of a new project.

### Using a Custom Canvas

This library comes with **SDL canvas** to draw on:

```cpp
#include "cpurast.hpp" // cpurast core
#include "cpurast_sdl.hpp" // cpurast SDL canvas

SDL_Surface* surface = /* pointer initialization */;
...
std::unique_ptr<cr::canvas> cr_canvas;
...
cr_canvas = std::make_unique<cr::sdl_canvas>(surface);
```

You may also create and use a **custom canvas**:

```cpp
#include "canvas.hpp" // cpurast canvas interface

class custom_canvas : cr::canvas
{
...
}
```

```cpp
#include "cpurast.hpp" // cpurast core
// the following header file should include all required custom headers
#include "cpurast_custom.hpp" // cpurast custom canvas

std::unique_ptr<cr::canvas> cr_canvas;
...
cr_canvas = std::make_unique<custom_canvas>(/* custom constructor */);
```

> If you created a custom canvas, please consider [contributing](https://github.com/dominiksalvet/cpurast/issues/new) to cpurast.

## Used Sources

TODO

## Todo

* Use multiple threads
* use two rendering framebuffers
* Add support for texturing
* Add support for lighting
* Draw point, line, triangle
* Add support for shadows
* Add support for reflections
* Add support for various culling (remove some asserts)
* Add more examples
* Add repository topics
