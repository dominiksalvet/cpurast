# CPU Rasterizer

## How to Run

Requirements to run examples:

* [SDL2 library](https://www.libsdl.org/)
* [CMake tools](https://cmake.org/)
* A C++ compiler

Building examples that use **cpurast**:

```
mkdir build
cd build
cmake ..
make
```

Running a **triangle** example:

```
cd build/examples/triangle
./triangle
```

## How to Use

Minimum requirements to use the library:

* A C++ compiler

What may be useful:

* Delivered CMake build system
* Delivered examples of use

> It is suggested to start with an existing example, copy it to a new example directory, and start customizing it. Later, after some experience with cpurast, it may be used as the foundation of a new project.

## Custom Canvas

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
cr_canvas = std::make_unique<cr::custom_canvas>(/* custom constructor */);
```

## Features

* Z-buffering support
* Uses normalized device coordinates
* Cross platform, no dependencies

## Todo

* Use OpenMP or similar (e.g., for loops)
* Enable ignoring asserts for final compilation
* Try to use some SDL surface accelerations (e.g., SDL_SetSurfaceRLE)
* Use multiple threads
* Add support for texturing
* Add support for lighting
* Add support for vextex attributes
* Draw point, line, triangle
* Add support for shadows
* Add support for vertex and fragment shader
* Add support for various culling
* Optimize framebuffer operations (e.g., no write when not changed...)
* Viewport rendering
* Multiple framebuffer/VAO support
* Add more examples
