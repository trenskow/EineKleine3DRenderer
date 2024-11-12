//
//  Renderer.cpp
//  Tiny3DRenderer
//
//  Created by Kristian Trenskow on 09/11/2024.
//

#include <algorithm>
#include <map>

#include "Renderer.hpp"

#define TOLERANCE 1e-6

using namespace std;

Renderer::Renderer() : meshes() { }

Renderer::Renderer(
	const Meshes& meshes
) : meshes(meshes) { }

void Renderer::render(
	RenderResult& renderResult,
	float width,
	float height,
	Color faceColor,
	Color edgeColor,
	Camera camera,
	Renderer::FaceRenderOptions faceRenderOptions,
	Renderer::EdgeRenderOptions edgeRenderOptions
) const {

	Faces3d result;

	Matrix4x4 matrixProjection = Matrix4x4::projection(height / width);
	Matrix4x4 worldMatrix = Matrix4x4::identity();

	Color white(0.9, 0.9, 0.9, 1);

	vector<FaceRenderInformation> toRender;

	for (auto mesh : meshes) {

		for (auto face : mesh.faces) {

			FaceRenderInformation renderInformation;

			Mesh::Face3dExtended& faceMesh = renderInformation.mesh = face;
			Mesh::Face3dExtended& faceWorld = renderInformation.world = faceMesh * worldMatrix;

			if (edgeRenderOptions == EdgeRenderOptions::visible) {

				vector<Face3d> visibleAdjacentFaces;

				std::copy_if(faceWorld.adjacentFaces.cbegin(), faceWorld.adjacentFaces.cend(), back_inserter(visibleAdjacentFaces), [&](const Face3d& face) {

					if (!face.visibleFrom(camera.position)) {
						return false;
					}

					auto crossProduct = faceWorld.normal().crossProduct(face.normal());

					return !(fabs(crossProduct.x) < TOLERANCE && fabs(crossProduct.y) < TOLERANCE && fabs(crossProduct.z) < TOLERANCE);

				});

				map<FaceRenderInformation::OutputEdge, Edge3d> outputEdges;

				outputEdges.insert({ FaceRenderInformation::OutputEdgeP01, { faceWorld.p[0], faceWorld.p[1] } });
				outputEdges.insert({ FaceRenderInformation::OutputEdgeP12, { faceWorld.p[1], faceWorld.p[2] } });
				outputEdges.insert({ FaceRenderInformation::OutputEdgeP20, { faceWorld.p[2], faceWorld.p[0] } });

				for (auto const& [outputEdge, edge] : outputEdges) {
					for (auto adjacentFace : visibleAdjacentFaces) {
						for (auto adjacentEdge : adjacentFace.edges()) {
							if (edge == adjacentEdge) {
								renderInformation.outputEdge = (FaceRenderInformation::OutputEdge)(renderInformation.outputEdge | outputEdge);
							}
						}
					}
				}

			} else if (edgeRenderOptions == EdgeRenderOptions::wireframe) {
				renderInformation.outputEdge = static_cast<FaceRenderInformation::OutputEdge>(
					FaceRenderInformation::OutputEdge::OutputEdgeP01
						| FaceRenderInformation::OutputEdge::OutputEdgeP12
						| FaceRenderInformation::OutputEdge::OutputEdgeP20);
			}

			renderInformation.visibleFromCamera = faceWorld.visibleFrom(camera.position);
			renderInformation.color = Color(0, 0, 0, 0);

			Mesh::Face3dExtended faceView = faceWorld * camera.matrix;

			switch (faceRenderOptions) {
				case FaceRenderOptions::solid:
					renderInformation.color = faceColor;
					break;
				case FaceRenderOptions::shaded:
					renderInformation.color = faceColor.interpolate(white, max(0.0f, faceWorld.normal().dotProduct({ 1, 0, 1 })));
					break;
				default:
					break;
			}

			Face3d& faceProjected = renderInformation.projected = faceView * matrixProjection;

			faceProjected.p[0] /= faceProjected.p[0].w;
			faceProjected.p[1] /= faceProjected.p[1].w;
			faceProjected.p[2] /= faceProjected.p[2].w;
			faceProjected.p[0].w = 1;
			faceProjected.p[1].w = 1;
			faceProjected.p[2].w = 1;

			Vertex3d offsetView = { 1, 1, 0 };

			faceProjected.p[0] += offsetView;
			faceProjected.p[1] += offsetView;
			faceProjected.p[2] += offsetView;
			faceProjected.p[0].x *= 0.5f * width;
			faceProjected.p[0].y *= 0.5f * height;
			faceProjected.p[1].x *= 0.5f * width;
			faceProjected.p[1].y *= 0.5f * height;
			faceProjected.p[2].x *= 0.5f * width;
			faceProjected.p[2].y *= 0.5f * height;

			toRender.push_back(renderInformation);

		}

	}

	sort(result.begin(), result.end(), [](Face3d& t1, Face3d& t2) {
		float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
		float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
		return z1 > z2;
	});

	for (auto information : toRender) {

		if (information.visibleFromCamera && !information.color.isTransparent()) {
			renderResult.fills.push_back(RenderResult::Fill({
				Face2d({
					information.projected.p[0],
					information.projected.p[1],
					information.projected.p[2] }),
				information.color
			}));

		}

		if (information.outputEdge != FaceRenderInformation::OutputEdge::OutputEdgeNone) {

			auto edges = map<FaceRenderInformation::OutputEdge, Edge2d>({
				{ FaceRenderInformation::OutputEdgeP01, { Vertex2d(information.projected.p[0]), Vertex2d(information.projected.p[1]) } },
				{ FaceRenderInformation::OutputEdgeP12, { Vertex2d(information.projected.p[1]), Vertex2d(information.projected.p[2]) } },
				{ FaceRenderInformation::OutputEdgeP20, { Vertex2d(information.projected.p[2]), Vertex2d(information.projected.p[0]) } }
			});

			for (auto const& [outputEdge, edge] : edges) {
				if (information.outputEdge & outputEdge) {
					renderResult.strokes.push_back({
						edge,
						edgeColor
					});
				}
			}

		}

	}

}
