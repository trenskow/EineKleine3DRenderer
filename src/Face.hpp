//
//  Face.hpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 11/11/2024.
//

#ifndef Face_hpp
#define Face_hpp

#include <vector>

#include "Edge.hpp"
#include "Matrix.hpp"
#include "Vertex.hpp"

struct Face3d {

	Face3d operator*(const Matrix4x4& matrix) const;
	Face3d operator*(float scalar) const;
	Face3d& operator*=(float scaler);
	Face3d operator+(float scalar) const;
	Face3d& operator+=(float scaler);

	Edges3d edges() const;

	Vertex3d normal() const;

	bool visibleFrom(const Vertex3d& camera) const;

	Vertex3d p[3];

};

typedef std::vector<Face3d> Faces3d;

#endif /* Face_hpp */
