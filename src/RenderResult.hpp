//
//  RenderResult.hpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 12/11/2024.
//

#ifndef RenderResult_hpp
#define RenderResult_hpp

#include <vector>

#include "Vertex.hpp"
#include "Edge.hpp"
#include "Color.hpp"

struct RenderResult {

	struct Fill {
		Face2d face;
		Color color;
	};

	struct Stroke {
		Edge2d edge;
		Color color;
	};

	std::vector<Fill> fills;
	std::vector<Stroke> strokes;

};

#endif /* RenderResult_hpp */
