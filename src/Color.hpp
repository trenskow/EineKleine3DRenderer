//
//  Color.hpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 12/11/2024.
//

#ifndef Color_hpp
#define Color_hpp

struct Color {

	float red;
	float green;
	float blue;
	float alpha = 1;

	Color();

	Color(
		unsigned int hex);
	
	Color(
		float red,
		float green,
		float blue,
		float alpha = 1);

	Color interpolate(
		const Color& other,
		float factor) const;

};

#endif /* Color_hpp*/
