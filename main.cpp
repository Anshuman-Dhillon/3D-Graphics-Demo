#include <fstream>

#include "camera.h"
#include "rtactive.h"
#include "surface.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

using namespace std;



int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);

    world.add(make_shared<sphere>(point(0.0, -100.5, -1.0), 100.0, material_ground)); //ground
    world.add(make_shared<sphere>(point(0.5, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point(-0.5, 0.0, -1.0), 0.5, material_left));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 200;
    cam.max_depth = 100;

    cam.render(world);
}
