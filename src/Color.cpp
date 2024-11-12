//
//  Color.cpp
//  EineKleine3DRenderer
//
//  Created by Kristian Trenskow on 12/11/2024.
//

#include "Color.hpp"

Color::Color() : red(0), green(0), blue(0), alpha(1) { }

Color::Color(
	unsigned int rgb
) : alpha(1) {
	red = ((rgb >> 16) & 0xFF) / 255.0f;
	green = ((rgb >> 8) & 0xFF) / 255.0f;
	blue = (rgb & 0xFF) / 255.0f;
}

Color::Color(
	float red,
	float green,
	float blue,
	float alpha
) : red(red), green(green), blue(blue), alpha(alpha) { }

Color Color::interpolate(
	const Color &other,
	float factor
) const {
	return Color(
		red + (other.red - red) * factor,
		green + (other.green - green) * factor,
		blue + (other.blue - blue) * factor,
		alpha + (other.alpha - alpha) * factor);
}
