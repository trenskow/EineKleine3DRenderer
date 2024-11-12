//
//  Face.cpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 11/11/2024.
//

#include "Face.hpp"

Face3d Face3d::operator*(const Matrix4x4 &matrix) const {

	Face3d result;

	for (int i = 0; i < 3; i++) {
		result.p[i] = p[i] * matrix;
	}

	return result;

}

Face3d Face3d::operator*(float scalar) const {

	Face3d result;

	for (int i = 0; i < 3; i++) {
		result.p[i] = p[i] * scalar;
	}

	return result;

}

Face3d& Face3d::operator*=(float scalar) {

	for (int i = 0; i < 3; i++) {
		p[i] *= scalar;
	}

	return *this;

}

Face3d Face3d::operator+(float scalar) const {

	Face3d result;

	for (int i = 0; i < 3; i++) {
		result.p[i] = p[i] + scalar;
	}

	return result;

}

Face3d& Face3d::operator+=(float scalar) {

	for (int i = 0; i < 3; i++) {
		p[i] += scalar;
	}

	return *this;

}

Edges3d Face3d::edges() const {
	return {
		{ p[0], p[1] },
		{ p[1], p[2] },
		{ p[2], p[0] }
	};
}

Vertex3d Face3d::normal() const {
	return (p[1] - p[0]).crossProduct((p[2] - p[0])).normalized();
}

bool Face3d::visibleFrom(const Vertex3d &camera) const {
	return normal().dotProduct(p[0] - camera) < 0;
}
