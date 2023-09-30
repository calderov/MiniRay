#ifndef COLOR_H
#define COLOR_H

#include "vector3d.h"

// Set color as an alias for vector3d 
using color = vector3d;

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    // Divide the color by the number of samples
    double r = pixel_color.x() / samples_per_pixel;
    double g = pixel_color.y() / samples_per_pixel;
    double b = pixel_color.z() / samples_per_pixel;

    // Write the translated [0,255] value of each color component.
    static const interval intensity(0.000, 0.999);

    out << static_cast<int>(256 * intensity.clamp(r)) << ' '   // Red
        << static_cast<int>(256 * intensity.clamp(g)) << ' '   // Green
        << static_cast<int>(256 * intensity.clamp(b)) << '\n'; // Blue
}

#endif