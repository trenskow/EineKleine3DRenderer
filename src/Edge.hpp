//
//  Edge.hpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 11/11/2024.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <vector>
#include "Vertex.hpp"

template <typename T>
struct Edge {

	bool operator==(const Edge<T>& other) const {
		return (p[0] == other.p[0] && p[1] == other.p[1])
		|| (p[1] == other.p[0] && p[0] == other.p[1]);
	}

	T p[2];

};

typedef Edge<Vertex2d> Edge2d;
typedef Edge<Vertex3d> Edge3d;

typedef std::vector<Edge2d> Edges2d;
typedef std::vector<Edge3d> Edges3d;

#endif /* Edge_hpp */
