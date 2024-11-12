//
//  Vertex.hpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 10/11/2024.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include "Matrix.hpp"

struct Vertex3d;

struct Vertex2d {

	Vertex2d() = default;

	Vertex2d(
		float x = 0,
		float y = 0);

	Vertex2d(const Vertex3d& Vertex);

	Vertex2d operator*(float scalar) const;
	Vertex2d& operator*=(float scaler);

	Vertex2d operator*(const Vertex2d& rhs) const;
	Vertex2d& operator*=(const Vertex2d& rhs);

	Vertex2d operator+(float scalar) const;
	Vertex2d& operator+=(float scaler);

	Vertex2d operator+(Vertex2d rhs) const;
	Vertex2d& operator+=(Vertex2d rhs);

	Vertex2d operator-(float scalar) const;
	Vertex2d& operator-=(float scaler);

	Vertex2d operator-(Vertex2d rhs) const;
	Vertex2d& operator-=(Vertex2d rhs);

	Vertex2d operator/(float scalar) const;
	Vertex2d& operator/=(float scalar);

	Vertex2d operator/(Vertex2d rhs) const;
	Vertex2d& operator/=(Vertex2d rhs);

	bool operator==(const Vertex2d& other) const;

	float x = 0;
	float y = 0;

};

struct Vertex3d {

	Vertex3d operator*(const Matrix4x4& matrix) const;
	Vertex3d& operator*= (const Matrix4x4& matrix);

	Vertex3d operator*(float scalar) const;
	Vertex3d& operator*=(float scaler);

	Vertex3d operator*(const Vertex3d& rhs) const;
	Vertex3d& operator*=(const Vertex3d& rhs);

	Vertex3d operator+(float scalar) const;
	Vertex3d& operator+=(float scaler);

	Vertex3d operator+(Vertex3d rhs) const;
	Vertex3d& operator+=(Vertex3d rhs);

	Vertex3d operator-(float scalar) const;
	Vertex3d& operator-=(float scaler);

	Vertex3d operator-(Vertex3d rhs) const;
	Vertex3d& operator-=(Vertex3d rhs);

	Vertex3d operator/(float scalar) const;
	Vertex3d& operator/=(float scalar);

	Vertex3d operator/(Vertex3d rhs) const;
	Vertex3d& operator/=(Vertex3d rhs);

	bool operator==(const Vertex3d& other) const;

	float dotProduct(const Vertex3d& other) const;
	float length() const;
	Vertex3d normalized() const;
	Vertex3d crossProduct(const Vertex3d& other) const;

	Matrix4x4 pointAt(const Vertex3d& target) const;

	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;

};

#endif /* Vertex_hpp */
