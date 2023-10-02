#ifndef COLOR_H
#define COLOR_H

#include "vector3d.h"

// Set color as an alias for vector3d 
using color = vector3d;

inline color gamma_correction(color pixel_color, int samples_per_pixel) {
    // Divide the color by the number of samples
    double r = pixel_color.x() / samples_per_pixel;
    double g = pixel_color.y() / samples_per_pixel;
    double b = pixel_color.z() / samples_per_pixel;

    // Apply gamma correction
    r = sqrt(r);
    g = sqrt(g);
    b = sqrt(b);

    // Truncate corrected values to be from 0 to 1
    static const interval intensity(0.000, 0.999);
    
    // Return gamma corrected color
    return color(intensity.clamp(r), intensity.clamp(g), intensity.clamp(b));
}

// Write color to output stream
void write_color(std::ostream &out, color pixel_color) {
    out << static_cast<int>(256 * pixel_color.x()) << ' '   // Red
        << static_cast<int>(256 * pixel_color.y()) << ' '   // Green
        << static_cast<int>(256 * pixel_color.z()) << '\n'; // Blue
}

#endif