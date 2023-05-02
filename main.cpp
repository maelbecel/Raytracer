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
#include "Shapes/Triangle.hpp"
#include "Shapes/Plan.hpp"

raytracer::Scene final_scene()
{
    raytracer::Scene objects;

    auto light_red = std::make_shared<raytracer::DiffuseLight>(Math::Color(20, 0, 0));
    auto light_green = std::make_shared<raytracer::DiffuseLight>(Math::Color(0, 20, 0));
    auto light_blue = std::make_shared<raytracer::DiffuseLight>(Math::Color(0, 0, 20));
    auto light_yellow = std::make_shared<raytracer::DiffuseLight>(Math::Color(10, 10, 0));

    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(.8, .8, .8));
    auto green = std::make_shared<raytracer::Lambertian>(Math::Color(.1, .8, .3));
    auto glass = std::make_shared<raytracer::Dielectric>(1.5);
    auto metalle = std::make_shared<raytracer::Metal>(Math::Color(.8, .8, .8), 0);
    auto metal = std::make_shared<raytracer::Metal>(Math::Color(.8, .4, .3), 0.5);
    auto blue = std::make_shared<raytracer::Lambertian>(Math::Color(.1, .3, .8));

    objects.addObject(std::make_shared<raytracer::YRotation>(std::make_shared<raytracer::XZRectangle>(0, 100, 455, 555, 554, light_blue), 0));
    // objects.addObject(std::make_shared<raytracer::YRotation>(std::make_shared<raytracer::XZRectangle>(0, 100, 0, 100, 554, light_red), 0));
    // objects.addObject(std::make_shared<raytracer::YRotation>(std::make_shared<raytracer::XZRectangle>(455, 555, 0, 100, 554, light_yellow), 0));
    // objects.addObject(std::make_shared<raytracer::YRotation>(std::make_shared<raytracer::XZRectangle>(455, 555, 455, 555, 554, light_green), 0));



    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 555, metal));
    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 0, metal));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 0, white));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 555, metal));
    objects.addObject(std::make_shared<raytracer::XYRectangle>(0, 555, 0, 555, 555, metal));
    objects.addObject(std::make_shared<raytracer::XYRectangle>(-10000, 10000, -10000, 10000, -801, white));

    objects.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(320, 200, 100), 80, white));
    objects.addObject(std::make_shared<raytracer::Translation>(std::make_shared<raytracer::YRotation>(std::make_shared<raytracer::Box>(Math::Color(0, 0, 0), Math::Vector3D(165, 330, 165), metalle), 15), Math::Vector3D(265, 0, 295)));

    return objects;
}

int main ()
{
    // Parser

    Parser::Parser parser("scene.cfg");
    raytracer::Camera cam = parser.parseCamera();

    // Image

    const int image_height = parser.getImageHeight();
    const int image_width = parser.getImageHeight() * cam.getRatio();
    const int samples_per_pixel = parser.getSamplesPerPixel();
    const int depth = parser.getMaxDepth();

    // Scene

    raytracer::Scene world = final_scene();


    // Camera

    Math::Vector3D background(0, 0, 0);


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

