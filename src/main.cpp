#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    // Materials
    auto R = cos(pi/4);

    auto material_left  = make_shared<lambertian>(color(0,0,1));
    auto material_right = make_shared<lambertian>(color(1,0,0));

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3d(-R, 0, -1), R, material_left));
    world.add(make_shared<sphere>(point3d( R, 0, -1), R, material_right));
    
    // Camera
    camera cam;
    cam.image_width = 1366;
    cam.image_height = 720;
    cam.samples_per_pixel = 50;
    cam.max_depth = 10;
    cam.vfov = 90;

    // Render
    cam.render(world);

    return 0;
}