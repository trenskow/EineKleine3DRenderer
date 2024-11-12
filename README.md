# EineKleine3DRenderer

This is a small software 3D renderer written in C++.

## Usage

````c++
#include <vector>

#include "Renderer.hpp"

auto renderer = Renderer();

renderer.loadModel("MyModel.obj");

RenderResult result;

renderer.render(
	result, // Will be filled with tringles to stroke and fill.
	200, // Width,
	200, // Height,
	Color(0, 0, 0), // Face color,
	Color(255, 255, 255), // Stroke color,
	Camera.lookAtTarget(
		Vertex3d({ 2.5, 0, 0 }), // Position,
		Vertex3d({ 0, 0, 0 }) // Target
	),
	Renderer::FaceRenderOption::shaded,     // Valid: solid (default), shaded, none
	Renderer::FaceRenderOptions::none       // Valid: visible, wireframe, none (default)
);

/* Draw `result.fills` and `result.strokes` to a canvas. */
````

# License

See license in LICENSE.
