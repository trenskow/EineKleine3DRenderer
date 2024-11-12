//
//  Mesh.cpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 12/11/2024.
//

#include <fstream>
#include <sstream>
#include <algorithm>

#include "Mesh.hpp"
#include "Face.hpp"

using namespace std;

Mesh::Face3dExtended::Face3dExtended(
	const Face3dExtended &other
) : Face3d(other), adjacentFaces(other.adjacentFaces) { }

Mesh::Face3dExtended Mesh::Face3dExtended::operator*(
	const Matrix4x4 &rhs
) const {

	Face3dExtended result;

	result.p[0] = p[0] * rhs;
	result.p[1] = p[1] * rhs;
	result.p[2] = p[2] * rhs;

	transform(adjacentFaces.cbegin(), adjacentFaces.cend(), back_inserter(result.adjacentFaces), [&](const Face3d& face) {
		return face * rhs;
	});

	return result;

}

bool Mesh::loadFromObjectFile(
	const string &objectFile
) {

	ifstream file(objectFile);

	if (!file.is_open()) {
		return false;
	}

	vector<Vertex3d> vertices;

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

				Mesh::Face3dExtended face;
				
				face.p[0] = vertices[index[0] - 1];
				face.p[1] = vertices[index[1] - 1];
				face.p[2] = vertices[index[2] - 1];

				faces.push_back(face);

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

	return true;

}

Mesh Mesh::applyingTransform(
	Matrix4x4 matrix
) const {

	Mesh result = *this;

	result.applyTransform(matrix);

	return result;

}

void Mesh::applyTransform(
	Matrix4x4 matrix
) {
	transform(faces.cbegin(), faces.cend(), faces.begin(), [&](const Mesh::Face3dExtended& face) {
		return face * matrix;
	});
}
