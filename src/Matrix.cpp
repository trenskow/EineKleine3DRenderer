//
//  Matrix.cpp
//  Tiny3DEngine
//
//  Created by Kristian Trenskow on 10/11/2024.
//

#include <algorithm>

#include "Matrix.hpp"

Matrix4x4 Matrix4x4::identity() {
	return {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

Matrix4x4 Matrix4x4::rotationZ(float theta) {
	return {
		cosf(theta), sinf(theta), 0, 0,
		-sinf(theta), cosf(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

Matrix4x4 Matrix4x4::rotationX(float theta) {
	return {
		1, 0, 0, 0,
		0, cosf(theta), sinf(theta), 0,
		0, -sinf(theta), cosf(theta), 0,
		0, 0, 0, 1
	};
}

Matrix4x4 Matrix4x4::rotationY(float theta) {
	return {
		cosf(theta), 0, -sinf(theta), 0,
		0, 1, 0, 0,
		sinf(theta), 0, cosf(theta), 0,
		0, 0, 0, 1
	};
}

Matrix4x4 Matrix4x4::translation(
	float x,
	float y,
	float z
) {
	return {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
}

Matrix4x4 Matrix4x4::projection(
								float aspectRatio,
								float fov,
								float near,
								float far
								) {

	Matrix4x4 matrixProjection;

	float fovRad = 1.0f / tan(fov * 0.5f / 180.0f * 3.14159f);

	matrixProjection.m[0][0] = aspectRatio * fovRad;
	matrixProjection.m[1][1] = fovRad;
	matrixProjection.m[2][2] = far / (far - near);
	matrixProjection.m[3][2] = (-far * near) / (far - near);
	matrixProjection.m[2][3] = 1.0f;
	matrixProjection.m[3][3] = 0.0f;

	return matrixProjection;

}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) const {

	Matrix4x4 result;

	for (int c = 0; c < 4; c++) {
		for (int r = 0; r < 4; r++) {
			result.m[r][c] = m[r][0] * other.m[0][c] + m[r][1] * other.m[1][c] + m[r][2] * other.m[2][c] + m[r][3] * other.m[3][c];
		}
	}

	return result;

}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4 &other) {
	*this = *this * other;
	return *this;
}

Matrix4x4 Matrix4x4::quickInverse() const {

	Matrix4x4 result;

	result.m[0][0] = m[0][0];
	result.m[0][1] = m[1][0];
	result.m[0][2] = m[2][0];
	result.m[0][3] = 0;

	result.m[1][0] = m[0][1];
	result.m[1][1] = m[1][1];
	result.m[1][2] = m[2][1];
	result.m[1][3] = 0;

	result.m[2][0] = m[0][2];
	result.m[2][1] = m[1][2];
	result.m[2][2] = m[2][2];
	result.m[2][3] = 0;

	result.m[3][0] = -(m[3][0] * result.m[0][0] + m[3][1] * result.m[1][0] + m[3][2] * result.m[2][0]);
	result.m[3][1] = -(m[3][0] * result.m[0][1] + m[3][1] * result.m[1][1] + m[3][2] * result.m[2][1]);
	result.m[3][2] = -(m[3][0] * result.m[0][2] + m[3][1] * result.m[1][2] + m[3][2] * result.m[2][2]);
	result.m[3][3] = 1;

	return result;

}
