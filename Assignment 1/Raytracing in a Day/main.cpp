#include "rtday.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>

using namespace std;


//linear blending based on the height of our given y coordinate.
//if we don't hit in the sphere our color is just t -0.5

color ray_color(const ray& r, const hittable& world)
{
    hit_record rec;
    if (world.hit(r, 0.0, infinity, rec))
    {
        //normalized vector of our pixel color for the sphere.
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    //return our "blended value" return blue when t = 1.0, return white on 0.0.
    //this is our first form of lerp
    //blendedValue = (1.0 - t) * vec3 startValue(white) + t * endValue(sky blue);
    return (1.0f - t) * color(1.0, 1.0, 1.0) + t * color(0.5f, 0.7f, 1.0f);
}

int main() 
{

    //Image
    const float aspect_ratio = 16.0f / 9.0f;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    //Get rid of the need for casting with - 1 on image_width / height
    const int imageWidth = image_width - 1;
    const int imageHeight = image_height - 1;

    // "World"
    hittable_list world;
    //our initial normalized sphere in center screen
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5f));
    //Our colored grass underneath the sphere made by making a huge sphere just outside of our rendered scene.
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100.0f));

    // Camera
    float viewport_height = 2.0f;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0;

    vec3 origin = point3(0, 0, 0);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            //cleaner calling of drawing to our image.
            //our uv coordinate like in Shadertoy with respect to our resolution.
            float u = float(i) / imageWidth;
            float v = float(j) / imageHeight;
            //pass our origin, then slide in our uv from our bottom left along the rest of the screen with respect to origin.
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r, world);
            write_color(cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}