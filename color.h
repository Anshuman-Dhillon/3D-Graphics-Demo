#define COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return std::sqrt(linear_component);

	return 0;
}

void write_color(std::ostream& out, const color& pixelcolor) {
	auto red = pixelcolor.x();
	auto green = pixelcolor.y();
	auto blue = pixelcolor.z();

	red = linear_to_gamma(red);
	green = linear_to_gamma(green);
	blue = linear_to_gamma(blue);

	static const interval intensity(0.000, 0.999);
	int r = int(256 * intensity.clamp(red));
	int g = int(256 * intensity.clamp(green));
	int b = int(256 * intensity.clamp(blue));

	out << r << ' ' << g << ' ' << b << '\n';
}