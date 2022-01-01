#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

// Create ray_color function that takes in ray object and returns color object
color ray_color(const ray& r)
{
    // Unit direction object of ray r
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    // Blends between blue and white (0 is white, 1 is blue, 0.0 < t < 1.0)
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    point3 origin = point3(0, 0, 0);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Loop through RGB colors (left to right and top to bottom)
    for (int j = image_height - 1; j >= 0; --j) {
        // Print error to console (will not be directed to .ppm file)
        // Use .\RayTracing.ppm 2> Image.txt if you want to direct to .txt
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);

            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            // Use write_color to scale back to normal RGB scale
            write_color(std::cout, pixel_color);

            //// Using color/vec3 class to make and print pixel
            //color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            //write_color(std::cout, pixel_color);

            ////auto r = double(i) / (image_width - 1);
            ////auto g = double(j) / (image_height - 1);
            ////auto b = 0.25;

            ////int ir = static_cast<int>(255.999 * r);
            ////int ig = static_cast<int>(255.999 * g);
            ////int ib = static_cast<int>(255.999 * b);

            ////// Display to console (will be written to .ppm file)
            ////// Use .\RayTracing.ppm 1> Image.txt OR .\RayTracing.exe > Image.ppm
            ////std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    // Print error to console (will not be directed to .ppm file)
    // Use .\RayTracing.ppm 2> Image.txt if you want to direct to .txt
    std::cerr << "\nDone.\n";
}