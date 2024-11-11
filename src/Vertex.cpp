//
//  Vertex.cpp
//  Tiny3DEngine
//
//  Created by Kristian Trenskow on 10/11/2024.
//

#include <algorithm>

#include "Vertex.hpp"

Vertex2d::Vertex2d(
	const Vertex3d &Vertex
) : x(Vertex.x), y(Vertex.y) { }

Vertex2d::Vertex2d(
	float x,
	float y
) : x(x), y(y) { }

Vertex2d Vertex2d::operator*(float scalar) const {
	return { x * scalar, y * scalar };
}

Vertex2d& Vertex2d::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vertex2d Vertex2d::operator*(const Vertex2d &rhs) const {
	return { x * rhs.x, y * rhs.y };
}

Vertex2d& Vertex2d::operator*=(const Vertex2d &rhs) {
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vertex2d Vertex2d::operator+(float scalar) const {
	return { x + scalar, y + scalar };
}

Vertex2d& Vertex2d::operator+=(float scalar) {
	x += scalar;
	y += scalar;
	return *this;
}

Vertex2d Vertex2d::operator+(Vertex2d rhs) const {
	return { x + rhs.x, y + rhs.y };
}

Vertex2d& Vertex2d::operator+=(Vertex2d rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vertex2d Vertex2d::operator-(float scalar) const {
	return { x - scalar, y - scalar };
}

Vertex2d& Vertex2d::operator-=(float scalar) {
	x -= scalar;
	y -= scalar;
	return *this;
}

Vertex2d Vertex2d::operator-(Vertex2d rhs) const {
	return { x - rhs.x, y - rhs.y };
}

Vertex2d& Vertex2d::operator-=(Vertex2d rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vertex2d Vertex2d::operator/(float scalar) const {
	return { x / scalar, y / scalar };
}

Vertex2d& Vertex2d::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

Vertex2d Vertex2d::operator/(Vertex2d rhs) const {
	return { x / rhs.x, y / rhs.y, };
}

Vertex2d& Vertex2d::operator/=(Vertex2d rhs) {
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

bool Vertex2d::operator==(const Vertex2d &other) const {
	return x == other.x && y == other.y;
}

Vertex3d Vertex3d::operator*(const Matrix4x4 &matrix) const {

	Vertex3d result;

	result.x = x * matrix.m[0][0] + y * matrix.m[1][0] + z * matrix.m[2][0] + w * matrix.m[3][0];
	result.y = x * matrix.m[0][1] + y * matrix.m[1][1] + z * matrix.m[2][1] + w * matrix.m[3][1];
	result.z = x * matrix.m[0][2] + y * matrix.m[1][2] + z * matrix.m[2][2] + w * matrix.m[3][2];
	result.w = x * matrix.m[0][3] + y * matrix.m[1][3] + z * matrix.m[2][3] + w * matrix.m[3][3];

	return result;

}

Vertex3d Vertex3d::operator*(float scalar) const {
	return { x * scalar, y * scalar, z * scalar };
}

Vertex3d& Vertex3d::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vertex3d Vertex3d::operator*(const Vertex3d &rhs) const {
	return { x * rhs.x, y * rhs.y, z * rhs.z };
}

Vertex3d& Vertex3d::operator*=(const Vertex3d &rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

Vertex3d Vertex3d::operator+(float scalar) const {
	return { x + scalar, y + scalar, z + scalar };
}

Vertex3d& Vertex3d::operator+=(float scalar) {
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
}

Vertex3d Vertex3d::operator+(Vertex3d rhs) const {
	return { x + rhs.x, y + rhs.y, z + rhs.z };
}

Vertex3d& Vertex3d::operator+=(Vertex3d rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vertex3d Vertex3d::operator-(float scalar) const {
	return { x - scalar, y - scalar, z - scalar };
}

Vertex3d& Vertex3d::operator-=(float scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return *this;
}

Vertex3d Vertex3d::operator-(Vertex3d rhs) const {
	return { x - rhs.x, y - rhs.y, z - rhs.z };
}

Vertex3d& Vertex3d::operator-=(Vertex3d rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vertex3d Vertex3d::operator/(float scalar) const {
	return { x / scalar, y / scalar, z / scalar };
}

Vertex3d& Vertex3d::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vertex3d Vertex3d::operator/(Vertex3d rhs) const {
	return { x / rhs.x, y / rhs.y, z / rhs.z };
}

Vertex3d& Vertex3d::operator/=(Vertex3d rhs) {
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

bool Vertex3d::operator==(const Vertex3d &other) const {
	return x == other.x && y == other.y && z == other.z;
}

float Vertex3d::dotProduct(const Vertex3d &other) const {
	return x * other.x + y * other.y + z * other.z;
}

float Vertex3d::length() const {
	return sqrtf(dotProduct(*this));
}

Vertex3d Vertex3d::normalized() const {
	float length = this->length();
	return { x / length, y / length, z / length, w };
}

Vertex3d Vertex3d::crossProduct(const Vertex3d &other) const {
	return {
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	};
}

Matrix4x4 Vertex3d::pointAt(const Vertex3d &target) const {

	static const Vertex3d up = { 0, 1, 0 };

	Vertex3d forward = (target - *this).normalized();

	Vertex3d a = forward * up.dotProduct(forward);
	Vertex3d newUp = (up - a).normalized();

	Vertex3d right = newUp.crossProduct(forward);

	return {
		right.x, right.y, right.z, 0,
		newUp.x, newUp.y, newUp.z, 0,
		forward.x, forward.y, forward.z, 0,
		x, y, z, 1
	};

}
