#include "rtweekend.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include "scene01.h"

#include <thread>

int main() {
    // World
    hittable_list world = get_scene_01();

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