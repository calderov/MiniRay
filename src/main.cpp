#include "rtweekend.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
    // Image
    int image_width = 1366;
    int image_height = 720;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3d(0, 0, -1), -0.5));
    world.add(make_shared<sphere>(point3d(0, -100.5, -1), 100));

    // Camera
    camera cam;
    cam.image_width = 1366;
    cam.image_height = 720;
    cam.samples_per_pixel = 50;
    cam.max_depth = 10;

    // Render
    cam.render(world);

    return 0;
}