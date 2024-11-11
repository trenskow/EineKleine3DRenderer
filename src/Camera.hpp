//
//  Camera.hpp
//  Tiny3DEngine
//
//  Created by Kristian Trenskow on 11/11/2024.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Vertex.hpp"
#include "Matrix.hpp"

struct Camera {

	static Camera lookInDirection(
		const Vertex3d& position,
		const Vertex3d& direction);

	static Camera lookAtTarget(
		const Vertex3d& position,
		const Vertex3d& target);

	Vertex3d position;
	Matrix4x4 matrix;

};

#endif /* Camera_hpp */
