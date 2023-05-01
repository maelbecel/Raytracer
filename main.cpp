/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** main
*/

#include "Camera.hpp"
#include "Scene.hpp"
#include "Material/Lambertian.hpp"
#include "Material/Metal.hpp"
#include "Material/Dielectric.hpp"
#include "Material/DiffuseLight.hpp"
#include "Shapes/MovingSphere.hpp"
#include "Shapes/Node.hpp"
#include "Shapes/XYRectangle.hpp"
#include "Shapes/XZRectangle.hpp"
#include "Shapes/YZRectangle.hpp"
#include "Shapes/Box.hpp"
#include "Shapes/ConstantMedium.hpp"
#include "Shapes/Translation.hpp"
#include "Shapes/YRotation.hpp"
#include "Texture/Checker.hpp"
#include "Texture/Noise.hpp"
#include "Texture/Image.hpp"
#include "Parser/Parser.hpp"

raytracer::Scene final_scene()
{
    raytracer::Scene objects;

    auto light = std::make_shared<raytracer::DiffuseLight>(Math::Color(15, 15, 5));
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(.8, .8, .8));
    auto green = std::make_shared<raytracer::Lambertian>(Math::Color(.1, .8, .3));
    auto glass = std::make_shared<raytracer::Dielectric>(1.5);

    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 555, white));
    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 0, white));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(213, 343, 227, 332, 554, light));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 0, white));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 555, white));
    objects.addObject(std::make_shared<raytracer::XYRectangle>(0, 555, 0, 555, 555, white));

    objects.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(220, 200, 150), 50, green));
    objects.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(150, 200, 50), 50, glass));


    return objects;
}

int main ()
{
    // Parser

    Parser::Parser parser("scene.cfg");

    // Image

    const auto aspect_ratio = (float)((float)parser.getImageWidth() / (float)parser.getImageHeight());
    const int image_width = parser.getImageWidth();
    const int image_height = parser.getImageHeight();
    const int samples_per_pixel = parser.getSamplesPerPixel();
    const int depth = parser.getMaxDepth();

    // Scene

    raytracer::Scene world = final_scene();


    // Camera

    Math::Vector3D background(0, 0, 0);
    Math::Vector3D lookfrom(278,278, -800);
    Math::Vector3D lookat(278 , 278 ,0);
    Math::Vector3D vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto vfov = 40.0;
    auto aperture = 0.1;

    raytracer::Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0, 1);

    // Render

    std::ofstream _file("Rendu.ppm", std::ios::binary);

    _file << "P6\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << image_height - j - 1 << " / " << image_height << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Math::Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                raytracer::Ray r = cam.getRay(u, v);
                pixel_color += world.rayColor(r, background, depth);
            }
            raytracer::Scene::writePixel(_file, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}

