#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"
#include "material.h"

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

class camera {
  private:
    point3d center;         // Camera center
    point3d pixel00_loc;    // Location of pixel 0, 0
    vector3d pixel_delta_u; // Offset to pixel to the right
    vector3d pixel_delta_v; // Offset to pixel below
    vector3d u, v, w;       // Camera frame basis vectors
    vector3d defocus_disk_u; // Defocus disk horizontal radius
    vector3d defocus_disk_v; // Defocus disk vertical radius
    std::vector<color> image;// Image result
    std::vector<int> render_progress; // Vector to keep track of the number of rows rendered by each thread

    void initialize() {
        // Setup viewport
        center = lookfrom;
        double theta = degrees_to_radians(vfov);
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h * focus_dist;
        double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Calculate the u, v, w unit basis vectors for the camera coordinate frame
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges
        vector3d viewport_u = viewport_width * u;
        vector3d viewport_v = viewport_height * -v;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel
        point3d viewport_upper_left = center - (focus_dist * w) -  viewport_u / 2 -  viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    
        // Calculate the camera defocus disk basis vector
        double defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;

        // Initialize output image
        image.resize(image_height * image_width);
        std::fill(image.begin(), image.end(), color(0, 0, 0));

        // Initialize render progress vector
        render_progress.resize(maxThreads);
        std::fill(render_progress.begin(), render_progress.end(), 0);

        // Ensure there is at least one thread for rendering the scene
        maxThreads = maxThreads > 0 ? maxThreads : 1;
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        hit_record rec;

        // Return early if no more light bounces are allowed
        if (depth <= 0) {
            return color(0, 0, 0);
        }

        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;

            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth-1, world);
            
            return color(0,0,0);
        }

        vector3d unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

    // Get a randomly sampled camera ray for the pixel location i, j
    // originating from the camera defocus disk
    ray get_ray(int i, int j) const {
        point3d pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        point3d pixel_sample = pixel_center + pixel_sample_square();
        
        vector3d ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        vector3d ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    // Returns a random point in the camera defocus disk
    point3d defocus_disk_sample() const {
        vector3d p = random_in_unit_disk();
        return center  + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    vector3d pixel_sample_square() const {
        double px = 0.5 + random_double();
        double py = 0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

    void render_thread(const hittable& world, int threadId, int minRow, int maxRow) {
        for (int j = minRow; j < maxRow; j++) {
            for (int i = 0; i < image_width; i++) {
                // Take random samples for each pixel
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    image[j * image_width + i] += ray_color(r, max_depth, world);
                }
            }
            render_progress[threadId] += 1;
        }
    }

    void print_render_progress() {
        std::clog << "\nRendering scene with " << maxThreads << " threads\n\n" << std::flush;
        int percent = 0;
        int lastPercent = -1;
        int rawProgress = 0;
        while (percent < 100) {
            for (int& n : render_progress) {
                rawProgress += n;
            }

            percent = (double)(rawProgress) / image_height * 100;

            // Print progress only if it has changed
            if (percent != lastPercent) {
                lastPercent = percent;
                std::clog << "\rRendering: " << percent << "% " << std::flush;
            }

            rawProgress = 0;
        }
        std::clog << "\rRendering: " << percent << "% " << std::flush;
        std::fill(render_progress.begin(), render_progress.end(), 0);
    }

  public:
    // Camera parameters
    int image_width = 1366;      // Image width
    int image_height = 720;      // Image height
    int samples_per_pixel = 10;  // Random samples per pixel
    int max_depth = 10;          // Maximum number of ray bounces into scene
    double vfov = 90;            // Vertical view angle (field of view)

    point3d lookfrom = point3d(0, 0, -1); // Point camera is looking from
    point3d lookat   = point3d(0, 0, 0);  // Point camera is looking at
    vector3d vup     = vector3d(0, 1, 0); // Camera-relative "up" direction

    double  defocus_angle = 0; // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

    int maxThreads = 1; // Max number of threads available for the render step

    void render(const hittable& world) {
        // Start render timer
        const auto start{std::chrono::steady_clock::now()};
        
        // Initialize camera
        initialize();

        // Spawn render threads
        std::vector<std::thread> threads;
        for (int i = 0; i < maxThreads; i++) {
            int offset = image_height / maxThreads;
            int minRow = i * offset;
            int maxRow = i < maxThreads - 1 ? minRow + offset : image_height;
            threads.push_back(std::thread(&camera::render_thread, this, std::ref(world), i, minRow, maxRow));
        }

        // Print render progress
        print_render_progress();

        // Await for render threads
        for (int i = 0; i < maxThreads; i++) {
            threads[i].join();
        }

        // Stop render timer and print elapsed time
        const auto end{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{end - start};
        std::clog << "\n\nRender completed in: " << elapsed_seconds.count() << " seconds" << std::flush;
    }

    void write_image() {
        std::clog << "\n\nSaving...\n" << std::flush;

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int i = 0; i < image.size(); i++) {
            // Get ith pixel from image
            color pixel_color = image[i];

            // Apply gamma correction
            pixel_color = gamma_correction(pixel_color, samples_per_pixel);

            // Write color to output stream
            write_color(std::cout, pixel_color);
        }

        std::clog << "\nDone\n";
    }
   
};

#endif