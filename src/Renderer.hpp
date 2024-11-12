//
//  Renderer.hpp
//  Tiny3DRenderer
//
//  Created by Kristian Trenskow on 09/11/2024.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <vector>

#include "Vertex.hpp"
#include "Matrix.hpp"
#include "Edge.hpp"
#include "Face.hpp"
#include "Camera.hpp"
#include "RenderResult.hpp"
#include "Color.hpp"
#include "Mesh.hpp"

class Renderer {

	public:

		Renderer();
		Renderer(const Renderer&) = default;
		Renderer(const Meshes& meshes);

		void render(
			RenderResult& renderResult,
			float width,
			float height,
			Color faceColor,
			Color edgeColor = Color(0, 0, 0, 0),
			Camera camera = Camera()
		) const;

	private:

		struct FaceRenderInformation {

			enum OutputEdge {
				None = 0 << 0,
				P01  = 1 << 0,
				P12  = 1 << 1,
				P20  = 1 << 2
			};

			Mesh::Face3dExtended mesh;
			Mesh::Face3dExtended world;
			Face3d projected;
			std::vector<Vertex3d> adjacentWorldFaces;
			Color color;

			OutputEdge outputEdge = OutputEdge::None;

		};

		Meshes meshes;

		inline friend FaceRenderInformation::OutputEdge operator|(FaceRenderInformation::OutputEdge a, FaceRenderInformation::OutputEdge b) {
			return static_cast<FaceRenderInformation::OutputEdge>(static_cast<int>(a) | static_cast<int>(b));
		}

};

#endif /* Renderer_hpp */
