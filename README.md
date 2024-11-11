# EineKleine3DRenderer

This is a small software 3D renderer written in C++.

## Usage

````c++
#include <vector>

#include "Renderer.hpp"

auto renderer = Renderer();

renderer.loadModel("MyModel.obj");

std::vector<Edge2d> edgesToDraw;

renderer.render(
  edgesToDraw, // Will be filled with 2D lines to draw.
  200, // Width,
  200, // Height,
  Camera.lookAtTarget(
    Vertex3d({ 2.5, 0, 0 }), // Position,
    Vertex3d({ 0, 0, 0 }) // Target
  )
);

/* Draw `edgesToDraw` to a canvas. */
````

# License

See license in LICENSE.

