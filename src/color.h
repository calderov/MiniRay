#ifndef COLOR_H
#define COLOR_H

#include "vector3d.h"
#include <vector>

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

class color_palette {
  private:
    color rgb(double r, double g, double b) {
        r = r / 255;
        g = g / 255;
        b = b / 255;
        return color(r * r, g * g, b * b);
    }

  public:
    const color strawberry     = rgb(198,  38,  46); // #c6262e
    const color strawberry_100 = rgb(255, 140, 130); // #ff8c82
    const color strawberry_300 = rgb(237,  83,  83); // #ed5353
    const color strawberry_500 = rgb(198,  38,  46); // #c6262e
    const color strawberry_700 = rgb(161,   7,   5); // #a10705
    const color strawberry_900 = rgb(122,   0,   0); // #7a0000
    const color orange         = rgb(243, 115,  41); // #f37329
    const color orange_100     = rgb(255, 194, 125); // #ffc27d
    const color orange_300     = rgb(255, 161,  84); // #ffa154
    const color orange_500     = rgb(243, 115,  41); // #f37329
    const color orange_700     = rgb(204,  59,   2); // #cc3b02
    const color orange_900     = rgb(166,  33,   0); // #a62100
    const color banana         = rgb(249, 196,  64); // #f9c440
    const color banana_100     = rgb(255, 243, 148); // #fff394
    const color banana_300     = rgb(255, 225, 107); // #ffe16b
    const color banana_500     = rgb(249, 196,  64); // #f9c440
    const color banana_700     = rgb(212, 142,  21); // #d48e15
    const color banana_900     = rgb(173,  95,   0); // #ad5f00
    const color lime           = rgb(104, 183,  35); // #68b723
    const color lime_100       = rgb(209, 255, 130); // #d1ff82
    const color lime_300       = rgb(155, 219,  77); // #9bdb4d
    const color lime_500       = rgb(104, 183,  35); // #68b723
    const color lime_700       = rgb( 58, 145,   4); // #3a9104
    const color lime_900       = rgb( 32, 107,   0); // #206b00
    const color mint           = rgb( 40, 188, 163); // #28bca3
    const color mint_100       = rgb(137, 255, 221); // #89ffdd
    const color mint_300       = rgb( 67, 214, 181); // #43d6b5
    const color mint_500       = rgb( 40, 188, 163); // #28bca3
    const color mint_700       = rgb( 14, 154, 131); // #0e9a83
    const color mint_900       = rgb(  0, 115, 103); // #007367
    const color blueberry      = rgb( 54, 137, 230); // #3689e6
    const color blueberry_100  = rgb(140, 213, 255); // #8cd5ff
    const color blueberry_300  = rgb(100, 186, 255); // #64baff
    const color blueberry_500  = rgb( 54, 137, 230); // #3689e6
    const color blueberry_700  = rgb( 13,  82, 191); // #0d52bf
    const color blueberry_900  = rgb(  0,  46, 153); // #002e99
    const color grape          = rgb(165, 109, 226); // #a56de2
    const color grape_100      = rgb(228, 198, 250); // #e4c6fa
    const color grape_300      = rgb(205, 158, 247); // #cd9ef7
    const color grape_500      = rgb(165, 109, 226); // #a56de2
    const color grape_700      = rgb(114,  57, 179); // #7239b3
    const color grape_900      = rgb( 69,  41, 129); // #452981
    const color bubblegum      = rgb(222,  62, 128); // #de3e80
    const color bubblegum_100  = rgb(254, 154, 184); // #fe9ab8
    const color bubblegum_300  = rgb(244, 103, 157); // #f4679d
    const color bubblegum_500  = rgb(222,  62, 128); // #de3e80
    const color bubblegum_700  = rgb(188,  36,  93); // #bc245d
    const color bubblegum_900  = rgb(145,  14,  56); // #910e38
    const color cocoa          = rgb(113,  83,  68); // #715344
    const color cocoa_100      = rgb(163, 144, 124); // #a3907c
    const color cocoa_300      = rgb(138, 113,  94); // #8a715e
    const color cocoa_500      = rgb(113,  83,  68); // #715344
    const color cocoa_700      = rgb( 87,  57,  45); // #57392d
    const color cocoa_900      = rgb( 61,  33,  27); // #3d211b
    const color silver         = rgb(171, 172, 174); // #abacae
    const color silver_100     = rgb(250, 250, 250); // #fafafa
    const color silver_300     = rgb(212, 212, 212); // #d4d4d4
    const color silver_500     = rgb(171, 172, 174); // #abacae
    const color silver_700     = rgb(126, 128, 135); // #7e8087
    const color silver_900     = rgb( 85,  87,  97); // #555761
    const color slate          = rgb( 72,  90, 108); // #485a6c
    const color slate_100      = rgb(149, 163, 171); // #95a3ab
    const color slate_300      = rgb(102, 120, 133); // #667885
    const color slate_500      = rgb( 72,  90, 108); // #485a6c
    const color slate_700      = rgb( 39,  52,  69); // #273445
    const color slate_900      = rgb( 14,  20,  31); // #0e141f
    const color black          = rgb( 51,  51,  51); // #333333
    const color black_100      = rgb(102, 102, 102); // #666666
    const color black_300      = rgb( 77,  77,  77); // #4d4d4d
    const color black_500      = rgb( 51,  51,  51); // #333333
    const color black_700      = rgb( 26,  26,  26); // #1a1a1a
    const color black_900      = rgb(  0,   0,   0); // #000000

    std::vector<color> get_list_of_colors() {
        std::vector<color> list_of_colors;
        list_of_colors.push_back(strawberry);
        list_of_colors.push_back(strawberry_100);
        list_of_colors.push_back(strawberry_300);
        list_of_colors.push_back(strawberry_500);
        list_of_colors.push_back(strawberry_700);
        list_of_colors.push_back(strawberry_900);
        list_of_colors.push_back(orange);
        list_of_colors.push_back(orange_100);
        list_of_colors.push_back(orange_300);
        list_of_colors.push_back(orange_500);
        list_of_colors.push_back(orange_700);
        list_of_colors.push_back(orange_900);
        list_of_colors.push_back(banana);
        list_of_colors.push_back(banana_100);
        list_of_colors.push_back(banana_300);
        list_of_colors.push_back(banana_500);
        list_of_colors.push_back(banana_700);
        list_of_colors.push_back(banana_900);
        list_of_colors.push_back(lime);
        list_of_colors.push_back(lime_100);
        list_of_colors.push_back(lime_300);
        list_of_colors.push_back(lime_500);
        list_of_colors.push_back(lime_700);
        list_of_colors.push_back(lime_900);
        list_of_colors.push_back(mint);
        list_of_colors.push_back(mint_100);
        list_of_colors.push_back(mint_300);
        list_of_colors.push_back(mint_500);
        list_of_colors.push_back(mint_700);
        list_of_colors.push_back(mint_900);
        list_of_colors.push_back(blueberry);
        list_of_colors.push_back(blueberry_100);
        list_of_colors.push_back(blueberry_300);
        list_of_colors.push_back(blueberry_500);
        list_of_colors.push_back(blueberry_700);
        list_of_colors.push_back(blueberry_900);
        list_of_colors.push_back(grape);
        list_of_colors.push_back(grape_100);
        list_of_colors.push_back(grape_300);
        list_of_colors.push_back(grape_500);
        list_of_colors.push_back(grape_700);
        list_of_colors.push_back(grape_900);
        list_of_colors.push_back(bubblegum);
        list_of_colors.push_back(bubblegum_100);
        list_of_colors.push_back(bubblegum_300);
        list_of_colors.push_back(bubblegum_500);
        list_of_colors.push_back(bubblegum_700);
        list_of_colors.push_back(bubblegum_900);
        list_of_colors.push_back(cocoa);
        list_of_colors.push_back(cocoa_100);
        list_of_colors.push_back(cocoa_300);
        list_of_colors.push_back(cocoa_500);
        list_of_colors.push_back(cocoa_700);
        list_of_colors.push_back(cocoa_900);
        list_of_colors.push_back(silver);
        list_of_colors.push_back(silver_100);
        list_of_colors.push_back(silver_300);
        list_of_colors.push_back(silver_500);
        list_of_colors.push_back(silver_700);
        list_of_colors.push_back(silver_900);
        list_of_colors.push_back(slate);
        list_of_colors.push_back(slate_100);
        list_of_colors.push_back(slate_300);
        list_of_colors.push_back(slate_500);
        list_of_colors.push_back(slate_700);
        list_of_colors.push_back(slate_900);
        list_of_colors.push_back(black);
        list_of_colors.push_back(black_100);
        list_of_colors.push_back(black_300);
        list_of_colors.push_back(black_500);
        list_of_colors.push_back(black_700);
        list_of_colors.push_back(black_900);
        return list_of_colors;
    }
};

#endif