#include "color.h"
#include "vector3d.h"

#include <iostream>

using namespace std;

int main() {
    // Image
    int width = 1920;
    int height = 1080;

    // Render
    cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = 0; j < height; j++) {
        clog << "\rRendering: " << (int)((double)(j) / (height -  1) * 100) << "%" << ' ' << flush;
        for (int i = 0; i < width; i++) {
            double r = double(i) / (width - 1);
            double g = double(j) / (height - 1);
            double b = 0;

            color pixel_color = color(r, g, b);
            write_color(cout, pixel_color);
        }
    }

    clog << "\nDone\n";

    return 0;
}