#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <cstdlib> 
#include <vector>

hittable_list get_scene_03() {
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

    int index = 0;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 11; j++) {
            color albedo = list_of_colors[index % list_of_colors.size()];
            shared_ptr<material> sphere_material = make_shared<lambertian>(albedo);

            world.add(make_shared<sphere>(point3d(-14.5 + j * hspace, 1, -9 + i * vspace),  0.9,  sphere_material));
            world.add(make_shared<sphere>(point3d(-14.5 + j * hspace, 1, -9 + i * vspace),  1.0,  glass));

            index++;
        } 
    }

    return world;
}