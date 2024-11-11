//
//  Camera.cpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 11/11/2024.
//

#include "Camera.hpp"

Camera Camera::lookInDirection(
	const Vertex3d &position,
	const Vertex3d &direction
) {

	static const Vertex3d up = { 0, 1, 0 };

	Vertex3d right = up.crossProduct(direction).normalized();
	Vertex3d correctedUp = direction.crossProduct(right).normalized();

	Matrix4x4 rotationMatrix = {
		right.x, right.y, right.z, 0,
		correctedUp.x, correctedUp.y, correctedUp.z, 0,
		-direction.x, -direction.y, -direction.z, 0,
		0, 0, 0, 1
	};

	Matrix4x4 translationMatrix = {
		1, 0, 0, -position.x,
		0, 1, 0, -position.y,
		0, 0, 1, -position.z,
		0, 0, 0, 1
	};

	return Camera({
		position,
		(rotationMatrix * translationMatrix).quickInverse()
	});

}

Camera Camera::lookAtTarget(
	const Vertex3d &position,
	const Vertex3d &target
) {
	return Camera({
		position,
		position.pointAt(target).quickInverse()
	});
}
