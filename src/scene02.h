#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <cstdlib> 
#include <vector>

shared_ptr<material> random_material(std::vector<color> &list_of_colors) {
    double material_type = random_double();
    
    // Diffuse
    if (material_type < 0.8) {
        color albedo = list_of_colors[rand() % list_of_colors.size()];
        return make_shared<lambertian>(albedo);
    }

    // Metal
    else if (material_type < 0.95) {
        color albedo = list_of_colors[rand() % list_of_colors.size()];
        double fuzz = random_double(0, 0.5);
        return make_shared<metal>(albedo, fuzz);
    }

    // Glass
    else {
        return make_shared<dielectric>(1.458);
    }
}

hittable_list get_scene_02() {
    // Colors
    color_palette colors;
    std::vector<color> list_of_colors = colors.get_list_of_colors();

    // Materials
    shared_ptr<material>concrete = make_shared<lambertian>(color(.7, .7, .7));
    shared_ptr<material>glass = make_shared<dielectric>(1.5);

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3d(0,-1000,0), 1000, concrete));
    
    double vspace = 3;
    double hspace = 3;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 11; j++) {
            world.add(make_shared<sphere>(point3d(-12.5 + j * hspace, 1, -7.2 + i * vspace),  0.9,  random_material(list_of_colors)));
            world.add(make_shared<sphere>(point3d(-12.5 + j * hspace, 1, -7.2 + i * vspace),  1.0,  glass));
        } 
    }

    return world;
}