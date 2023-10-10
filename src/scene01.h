#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

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

hittable_list get_scene_01() {
    // Colors
    color_palette colors;

    // Materials
    shared_ptr<material>concrete = make_shared<lambertian>(colors.slate);
    shared_ptr<material>gold     = make_shared<metal>(colors.banana_500, 0.0);
    shared_ptr<material>silver   = make_shared<metal>(colors.silver, 0.0);
    shared_ptr<material>glass    = make_shared<dielectric>(1.5);

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3d(0,-1000,0), 1000, concrete));
    world.add(make_shared<sphere>(point3d(-4, 1, 0),  1.0,  gold));
    world.add(make_shared<sphere>(point3d(0,  1, 0),  1.0,  glass));
    world.add(make_shared<sphere>(point3d(4,  1, 0),  1.0,  silver));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double radius = 0.2;
            point3d center(a + 0.9 * random_double(), radius, b + 0.9 * random_double());

            if ((center - point3d(-4, 1, 0)).length() < 1.05 ||
                (center - point3d( 0, 1, 0)).length() < 1.05 ||
                (center - point3d( 4, 1, 0)).length() < 1.05)
                continue;

            world.add(make_shared<sphere>(center, radius, random_material()));
        }
    }

    return world;
}