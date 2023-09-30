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

    // Render
    cam.render(world);

    return 0;
}