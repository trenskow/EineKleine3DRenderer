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

		enum class FaceRenderOptions {
			none = 0,
			solid = 1,
			shaded = 2
		};

		enum class EdgeRenderOptions {
			none = 0 << 0,
			visible = 1 << 0,
			wireframe = 1 << 1
		};

		Renderer();
		Renderer(const Renderer&) = default;
		Renderer(const Meshes& meshes);

		void render(
			RenderResult& renderResult,
			float width,
			float height,
			Color faceColor,
			Color edgeColor = Color(0, 0, 0, 0),
			Camera camera = Camera(),
			FaceRenderOptions faceRenderOptions = FaceRenderOptions::shaded,
			EdgeRenderOptions edgeRenderOptions = EdgeRenderOptions::none
		) const;

		inline friend FaceRenderOptions operator|(FaceRenderOptions a, FaceRenderOptions b) {
			return static_cast<FaceRenderOptions>(static_cast<int>(a) | static_cast<int>(b));
		}

		inline friend EdgeRenderOptions operator|(EdgeRenderOptions a, EdgeRenderOptions b) {
			return static_cast<EdgeRenderOptions>(static_cast<int>(a) | static_cast<int>(b));
		}

	private:

		struct FaceRenderInformation {

			enum OutputEdge {
				OutputEdgeNone = 0 << 0,
				OutputEdgeP01  = 1 << 0,
				OutputEdgeP12  = 1 << 1,
				OutputEdgeP20  = 1 << 2
			};

			Mesh::Face3dExtended mesh;
			Mesh::Face3dExtended world;
			Face3d projected;
			std::vector<Vertex3d> adjacentWorldFaces;
			Color color;
			bool visibleFromCamera = false;

			OutputEdge outputEdge = OutputEdgeNone;

		};

		Meshes meshes;

		inline friend FaceRenderInformation::OutputEdge operator|(FaceRenderInformation::OutputEdge a, FaceRenderInformation::OutputEdge b) {
			return static_cast<FaceRenderInformation::OutputEdge>(static_cast<int>(a) | static_cast<int>(b));
		}

};

#endif /* Renderer_hpp */
