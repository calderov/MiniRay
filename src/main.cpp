#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <thread>

class materials_catalog {
  public:
    shared_ptr<material>concrete = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    shared_ptr<material>glass    = make_shared<dielectric>(1.5);
    shared_ptr<material>gold     = make_shared<metal>(create_color(221, 183, 130), 0.0);
    shared_ptr<material>silver   = make_shared<metal>(create_color(154, 163, 186), 0.0);

    shared_ptr<material> random_material() {
        double material_type = random_double();
        shared_ptr<material> result_material;
        
        // Diffuse
        if (material_type < 0.8) {
            color albedo = color::random() * color::random();
            result_material = make_shared<lambertian>(albedo);
        }

        // Metal
        else if (material_type < 0.95) {
            color albedo = color::random(0.5, 1);
            double fuzz = random_double(0, 0.5);
            result_material = make_shared<metal>(albedo, fuzz);
        }

        // Glass
        else {
            result_material = make_shared<dielectric>(1.5);
        }

        return result_material;
    }

    color create_color(double r, double g, double b) {
        r = r / 255;
        g = g / 255;
        b = b / 255;
        return color(r, g, b);
    }
};

int main() {
    // Materials
    materials_catalog materials;

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3d(0,-1000,0), 1000, materials.concrete));
    world.add(make_shared<sphere>(point3d(-4, 1, 0),  1.0,  materials.gold));
    world.add(make_shared<sphere>(point3d(0,  1, 0),  1.0,  materials.glass));
    world.add(make_shared<sphere>(point3d(4,  1, 0),  1.0,  materials.silver));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double radius = 0.2;
            point3d center(a + 0.9 * random_double(), radius, b + 0.9 * random_double());

            if ((center - point3d(-4, 1, 0)).length() < 1.05 ||
                (center - point3d( 0, 1, 0)).length() < 1.05 ||
                (center - point3d( 4, 1, 0)).length() < 1.05)
                continue;

        world.add(make_shared<sphere>(center, radius, materials.random_material()));
        }
    }

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

    cam.max_threads = std::thread::hardware_concurrency();

    // Render
    cam.render(world);

    // Write rendered image to stdout
    cam.write_image();

    return 0;
}