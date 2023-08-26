#include "color.h"
#include "ray.h"
#include "vector3d.h"

#include <iostream>

using namespace std;

color ray_color(const ray& r) {
    vector3d unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    int image_width = 1366;
    int image_height = 720;

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    point3d camera_center = point3d(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    vector3d viewport_u = vector3d(viewport_width, 0, 0);
    vector3d viewport_v = vector3d(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    vector3d pixel_delta_u = viewport_u / image_width;
    vector3d pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    point3d viewport_upper_left = camera_center - vector3d(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    point3d pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  
    // Render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        clog << "\rRendering: " << (int)((double)(j) / (image_height -  1) * 100) << "%" << ' ' << flush;
        for (int i = 0; i < image_width; i++) {
            point3d pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vector3d ray_direction = pixel_center - camera_center;
            ray r = ray(camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(cout, pixel_color);
        }
    }

    clog << "\nDone\n";

    return 0;
}