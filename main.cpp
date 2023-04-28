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

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Math::Vector3D center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Math::Vector3D(4, 0.2, 0)).len() > 0.9) {
                std::shared_ptr<raytracer::IMaterial> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Math::Vector3D::random() * Math::Vector3D::random();
                    sphere_material = std::make_shared<raytracer::Lambertian>(albedo);
                    world.addObject(std::make_shared<raytracer::Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Math::Vector3D::random(0.5, 1);
                    auto fuzz = random_double() * 0.5;
                    sphere_material = std::make_shared<raytracer::Metal>(albedo, fuzz);
                    world.addObject(std::make_shared<raytracer::Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<raytracer::Dielectric>(1.5);
                    world.addObject(std::make_shared<raytracer::Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
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

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 5;
    const int depth = 4;

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

