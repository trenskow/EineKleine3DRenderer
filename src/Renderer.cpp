//
//  Renderer.cpp
//  Tiny3DRenderer
//
//  Created by Kristian Trenskow on 09/11/2024.
//

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#include "Renderer.hpp"

#define TOLERANCE 1e-6

using namespace std;

Renderer::Renderer() : _faces() { }

bool Renderer::loadModel(const string& objectFile) {

	ifstream file(objectFile);

	if (!file.is_open()) {
		return false;
	}

	vector<Vertex3d> vertices;
	vector<Face3dExtended> faces;

	stringstream fileStringStream;

	fileStringStream << file.rdbuf();

	for (string line; getline(fileStringStream, line); ) {
		stringstream lineStream(line);

		char junk;

		switch (line[0]) {
			case 'v': {
				Vertex3d vertex;
				lineStream >> junk >> vertex.x >> vertex.y >> vertex.z;
				vertices.push_back(vertex);
				break;
			}
			case 'f': {
				int index[3];
				lineStream >> junk >> index[0] >> index[1] >> index[2];
				faces.push_back(Face3d({ vertices[index[0] - 1], vertices[index[1] - 1], vertices[index[2] - 1] }));
			}
			default:
				break;
		}

	}

	for (int idx1 = 0 ; idx1 < faces.size(); idx1++) {

		auto faces1Edges = faces[idx1].edges();

		for (int idx2 = idx1 + 1; idx2 < faces.size(); idx2++) {

			auto faces2Edges = faces[idx2].edges();

			for (auto edge1 : faces1Edges) {
				for (auto edge2 : faces2Edges) {
					if (edge1 == edge2) {
						faces[idx1].adjacentFaces.push_back(faces[idx2]);
						faces[idx2].adjacentFaces.push_back(faces[idx1]);
					}
				}
			}
		}

	}

	this->_faces = faces;

	return true;

}

void Renderer::render(
	Edges2d& edges,
	float width,
	float height,
	Camera camera
) const {

	Faces3d result;

	Matrix4x4 matrixProjection = Matrix4x4::projection(height / width);

	Matrix4x4 worldMatrix = Matrix4x4::identity();

	vector<FaceRenderInformation> toRender;

	for (auto face : _faces) {

		FaceRenderInformation renderInformation;

		Face3dExtended& faceModel = renderInformation.model = face;
		Face3dExtended& faceWorld = renderInformation.world = faceModel * worldMatrix;

		faceWorld.adjacentFaces = faceModel.adjacentFaces;

		std::transform(faceWorld.adjacentFaces.cbegin(), faceWorld.adjacentFaces.cend(), faceWorld.adjacentFaces.begin(), [&](const Face3d& face) {
			return face * worldMatrix;
		});

		vector<Face3d> visibleAdjacentFaces;

		std::copy_if(faceWorld.adjacentFaces.cbegin(), faceWorld.adjacentFaces.cend(), back_inserter(visibleAdjacentFaces), [&](const Face3d& face) {

			if (!face.visibleFrom(camera.position)) {
				return true;
			}

			auto crossProduct = faceWorld.normal().crossProduct(face.normal());

			return !(fabs(crossProduct.x) < TOLERANCE && fabs(crossProduct.y) < TOLERANCE && fabs(crossProduct.z) < TOLERANCE);

		});

		faceWorld.adjacentFaces = visibleAdjacentFaces;

		if (faceWorld.visibleFrom(camera.position)) {

			map<FaceRenderInformation::OutputEdge, Edge3d> outputEdges;

			outputEdges.insert({ FaceRenderInformation::OutputEdge::P01, { faceWorld.p[0], faceWorld.p[1] } });
			outputEdges.insert({ FaceRenderInformation::OutputEdge::P12, { faceWorld.p[1], faceWorld.p[2] } });
			outputEdges.insert({ FaceRenderInformation::OutputEdge::P20, { faceWorld.p[2], faceWorld.p[0] } });

			for (auto const& [outputEdge, edge] : outputEdges) {
				for (auto adjacentFace : faceWorld.adjacentFaces) {
					for (auto adjacentEdge : adjacentFace.edges()) {
						if (edge == adjacentEdge) {
							renderInformation.outputEdge = (FaceRenderInformation::OutputEdge)(renderInformation.outputEdge | outputEdge);
						}
					}
				}
			}

			Face3d& faceProjected = renderInformation.projected = (faceWorld * camera.matrix) * matrixProjection;

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
		if (information.outputEdge & FaceRenderInformation::OutputEdge::P01) {
			edges.push_back(Edge2d({ Vertex2d(information.projected.p[0]), Vertex2d(information.projected.p[1]) }));
		}
		if (information.outputEdge & FaceRenderInformation::OutputEdge::P12) {
			edges.push_back(Edge2d({ Vertex2d(information.projected.p[1]), Vertex2d(information.projected.p[2]) }));
		}
		if (information.outputEdge & FaceRenderInformation::OutputEdge::P20) {
			edges.push_back(Edge2d({ Vertex2d(information.projected.p[2]), Vertex2d(information.projected.p[0]) }));
		}
	}

}

Renderer::Face3dExtended::Face3dExtended(
	const Face3d &other
) : Face3d(other), adjacentFaces() { }
