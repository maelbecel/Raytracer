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
#include "Parser/Parser.hpp"

raytracer::Scene randomScene(void)
{
    raytracer::Scene world;

    auto ground_material = std::make_shared<raytracer::Lambertian>(Math::Color(0.5, 0.5, 0.5));
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0,-1000,0), 1000, ground_material));

    auto material1 = std::make_shared<raytracer::Dielectric>(1.5);
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<raytracer::Lambertian>(Math::Vector3D(0.4, 0.2, 0.1));
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<raytracer::Metal>(Math::Vector3D(0.7, 0.6, 0.5), 0.0);
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(4, 1, 0), 1.0, material3));
    return world;
}

int main ()
{
    // Parser

    Parser::Parser parser("scene.cfg");

    // Image

    const int image_width = parser.getImageWidth();
    const int image_height = parser.getImageHeight();
    const int samples_per_pixel = parser.getSamplesPerPixel();
    const int depth = parser.getMaxDepth();

    raytracer::Camera cam = parser.parseCamera();

    // Scene

    raytracer::Scene world = randomScene();

    // Render

    std::ofstream _file("ImageP6.ppm", std::ios::binary);

    _file << "P6\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << image_height - j - 1 << " / " << image_height << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Math::Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                raytracer::Ray r = cam.getRay(u, v);
                pixel_color += world.rayColor(r, depth);
            }
            raytracer::Scene::writePixel(_file, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}

