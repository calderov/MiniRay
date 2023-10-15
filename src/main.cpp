#include "rtweekend.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include "scene03.h"

#include <thread>

int main() {
    // World
    hittable_list world = get_scene_03();

    // Camera
    camera cam;

    cam.image_width       = 1920;
    cam.image_height      = 1080;
    cam.samples_per_pixel = 50;
    cam.max_depth         = 50;

    cam.vfov     = 17;
    cam.lookfrom = point3d(0, 80, 0);
    cam.lookat   = point3d(0, 0, 0);
    cam.vup      = vector3d(0, 0, -1);

    cam.defocus_angle = 0.1;
    cam.focus_dist    = 29.0;

    // Scene 1, cam settings
    // cam.vfov     = 20;
    // cam.lookfrom = point3d(13, 2, 3);
    // cam.lookat   = point3d(0, 0, 0);
    // cam.vup      = vector3d(0, 1, 0);
    //
    // cam.defocus_angle = 0.6;
    // cam.focus_dist    = 10.0;

    cam.max_threads = std::thread::hardware_concurrency();

    // Render
    cam.render(world);

    // Write rendered image to bitmap file
    std::string filename = "scene03.bmp";
    std::clog << "\n\nSaving " << filename << "...\n" << std::flush;
    cam.write_image(filename);
    std::clog << "\nDone\n";


    return 0;
}