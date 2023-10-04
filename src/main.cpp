#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    // Materials
    shared_ptr<material> ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    shared_ptr<material> material1 = make_shared<dielectric>(1.5);
    shared_ptr<material> material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    shared_ptr<material> material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3d(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3d center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3d(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                // Diffuse
                if (choose_mat < 0.8) {
                    color albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                } 
                
                // Metal
                else if (choose_mat < 0.95) {
                    color albedo = color::random(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                } 
                
                // Glass
                else {
                    sphere_material = make_shared<dielectric>(1.5);
                }

                world.add(make_shared<sphere>(center, 0.2, sphere_material));
            }
        }
    }

    world.add(make_shared<sphere>(point3d(0, 1, 0), 1.0, material1));
    world.add(make_shared<sphere>(point3d(-4, 1, 0), 1.0, material2));
    world.add(make_shared<sphere>(point3d(4, 1, 0), 1.0, material3));

    // Camera
    camera cam;

    cam.image_width       = 1920;
    cam.image_height      = 1080; 
    cam.samples_per_pixel = 50;
    cam.max_depth         = 10;

    cam.vfov     = 20;
    cam.lookfrom = point3d(13, 2, 3);
    cam.lookat   = point3d(0, 0, 0);
    cam.vup      = vector3d(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.maxThreads = 4;

    // Render
    cam.render(world);

    // Write rendered image to stdout
    cam.write_image();

    return 0;
}