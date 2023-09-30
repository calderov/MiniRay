#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    // Materials
    shared_ptr<material> material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    shared_ptr<material> material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    shared_ptr<material> material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
    shared_ptr<material> material_right  = make_shared<metal>(color(0.8, 0.6, 0.2));

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3d( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3d( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3d(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3d( 1.0,    0.0, -1.0),   0.5, material_right));

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