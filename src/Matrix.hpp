//
//  Matrix.hpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 10/11/2024.
//

#ifndef Matrix_hpp
#define Matrix_hpp

struct Matrix4x4 {

	static Matrix4x4 identity()
	;
	static Matrix4x4 rotationZ(
		float radians);

	static Matrix4x4 rotationX(
		float radians);

	static Matrix4x4 rotationY(
		float radians);

	static Matrix4x4 translation(
		float x,
		float y,
		float z);

	static Matrix4x4 scale(
		float x,
		float y,
		float z);

	static Matrix4x4 projection(
		float aspectRatio,
		float fov = 90.0f,
		float near = 0.1f,
		float far = 1000.f);

	Matrix4x4 operator*(const Matrix4x4& other) const;
	Matrix4x4& operator*=(const Matrix4x4& other);

	Matrix4x4 quickInverse() const;

	float m[4][4] = { 0 };

};

#endif /* Matrix_hpp */
