//
//  Mesh.hpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 12/11/2024.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>

#include "Matrix.hpp"
#include "Face.hpp"

struct Mesh {

	struct Face3dExtended: Face3d {

		Face3dExtended() = default;

		Face3dExtended(
			const Face3dExtended& other);

		Face3dExtended operator*(
			const Matrix4x4& rhs
		) const;

		std::vector<Face3d> adjacentFaces;

	};

	bool loadFromObjectFile(
		const std::string& objectFile);

	void applyTransform(
		Matrix4x4 matrix);

	Mesh applyingTransform(
		Matrix4x4 matrix
	) const;

	std::vector<Face3dExtended> faces = { };

};

typedef std::vector<Mesh> Meshes;

#endif /* Mesh_hpp */
