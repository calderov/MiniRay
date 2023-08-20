#ifndef COLOR_H
#define COLOR_H

#include "vector3d.h"

// Set color as an alias for vector3d 
using color = vector3d;

void write_color(std::ostream &out, color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '   // Red
        << static_cast<int>(255.999 * pixel_color.y()) << ' '   // Green
        << static_cast<int>(255.999 * pixel_color.z()) << '\n'; // Blue
}

#endif