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

class Renderer {

	public:
		Renderer();

		bool loadModel(
			const std::string& objectFile);

		void render(
			Edges2d& edges,
			float width,
			float height,
			Camera camera = Camera()
		) const;

		struct Face3dExtended: Face3d {

			Face3dExtended() = default;
			Face3dExtended(
				const Face3dExtended& other) = default;
			Face3dExtended(
				const Face3d& other);

			std::vector<Face3d> adjacentFaces;

		};

		struct FaceRenderInformation {

			enum OutputEdge {
				None = 0 << 0,
				P01  = 1 << 0,
				P12  = 1 << 1,
				P20  = 1 << 2
			};

			Face3dExtended model;
			Face3dExtended world;
			Face3d projected;
			std::vector<Vertex3d> adjacentWorldFaces;

			OutputEdge outputEdge = OutputEdge::None;

		};

		std::vector<Face3dExtended> _faces;

};

inline Renderer::FaceRenderInformation::OutputEdge operator|(Renderer::FaceRenderInformation::OutputEdge a, Renderer::FaceRenderInformation::OutputEdge b) {
	return static_cast<Renderer::FaceRenderInformation::OutputEdge>(static_cast<int>(a) | static_cast<int>(b));
}

#endif /* Renderer_hpp */
