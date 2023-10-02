#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    // Materials
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3d( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3d( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3d(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3d(-1.0,    0.0, -1.0),  -0.4, material_left));
    world.add(make_shared<sphere>(point3d( 1.0,    0.0, -1.0),   0.5, material_right));

    // Camera
    camera cam;
    cam.image_width = 1366;
    cam.image_height = 720;
    cam.samples_per_pixel = 50;
    cam.max_depth = 10;
    
    cam.vfov = 20;
    cam.lookfrom = point3d(-2, 2, 1);
    cam.lookat = point3d(0, 0, -1);
    cam.vup = vector3d(0, 1, 0);

    cam.defocus_angle = 10.0;
    cam.focus_dist = 3.4;

    // Render
    cam.render(world);

    return 0;
}