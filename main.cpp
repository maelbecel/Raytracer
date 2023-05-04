/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** main
*/

#define GIF false

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
#include "Shapes/ZRotation.hpp"
#include "Shapes/XRotation.hpp"
#include "Shapes/DirectionnalLight.hpp"
#include "Texture/Checker.hpp"
#include "Texture/Noise.hpp"
#include "Texture/Image.hpp"
#include "Parser/Parser.hpp"
#include "Shapes/Triangle.hpp"
#include "Shapes/Plan.hpp"
#include "Shapes/AmbientLight.hpp"
#include "GifCreator.hpp"

raytracer::Scene final_scene()
{
    raytracer::Scene objects;

    auto red   = std::make_shared<raytracer::Lambertian>(Math::Color(.65, .05, .05));
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(.73, .73, .73));
    auto green = std::make_shared<raytracer::Lambertian>(Math::Color(.12, .45, .15));
    auto light = std::make_shared<raytracer::DiffuseLight>(Math::Color(15, 15, 15));

    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 555, green));
    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 0, red));
    objects.addObject(std::make_shared<raytracer::DirectionnalLight>(std::make_shared<raytracer::XZRectangle>(213, 343, 227, 332, 554, light)));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 555, white));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 0, white));
    objects.addObject(std::make_shared<raytracer::XYRectangle>(0, 555, 0, 555, 555, white));

    auto metal = std::make_shared<raytracer::Metal>(Math::Color(.8, .85, .88), 0);
    std::shared_ptr<raytracer::IShape> box1 = std::make_shared<raytracer::Box>(Math::Vector3D(0,0,0), Math::Vector3D(165,330,165), metal);
    box1 = std::make_shared<raytracer::YRotation>(box1, 15);
    box1 = std::make_shared<raytracer::Translation>(box1, Math::Vector3D(265,0,295));
    objects.addObject(box1);

    auto glass = std::make_shared<raytracer::Dielectric>(1.5);
    objects.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(190,90,190), 90, glass));

    return objects;
}

raytracer::Scene room()
{
    raytracer::Scene objects;

    auto red   = std::make_shared<raytracer::Lambertian>(Math::Color(.65, .05, .05));
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(.73, .73, .73));
    auto green = std::make_shared<raytracer::Lambertian>(Math::Color(.12, .45, .15));
    auto light = std::make_shared<raytracer::DiffuseLight>(Math::Color(15, 15, 15));

    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 555, green));
    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 0, red));
    objects.addObject(std::make_shared<raytracer::DirectionnalLight>(std::make_shared<raytracer::XZRectangle>(213, 343, 227, 332, 554, light)));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 555, white));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 0, white));
    objects.addObject(std::make_shared<raytracer::XYRectangle>(0, 555, 0, 555, 555, white));

    auto metal = std::make_shared<raytracer::Metal>(Math::Color(.8, .85, .88), 0);
    std::shared_ptr<raytracer::IShape> box1 = std::make_shared<raytracer::Box>(Math::Vector3D(0,0,0), Math::Vector3D(165,330,165), metal);
    box1 = std::make_shared<raytracer::YRotation>(box1, 15);
    box1 = std::make_shared<raytracer::Translation>(box1, Math::Vector3D(265,0,295));
    objects.addObject(box1);

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
    Math::Vector3D background(0, 0, 0);



    raytracer::Scene world = final_scene();
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(0, 0,0));

    raytracer::Scene lights;
    lights.addObject(std::make_shared<raytracer::XZRectangle>(213, 343, 227, 332, 554, white));
    lights.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(190, 90, 190), 90, white));

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
                pixel_color += world.rayColor(r, background, std::make_shared<raytracer::Scene>(lights), depth);
            }
            raytracer::Scene::writePixel(_file, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
    _file.close();

    // Make gif

    #if GIF == true

    std::vector<std::string> ppm_buffer;
    int fps = 24;
    int time = 5;
    auto glass = std::make_shared<raytracer::Dielectric>(1.5);

    for (int i = 0; i < fps * time; i++) {
        std::string file;
        file += "P6\n";
        file += std::to_string(image_width) + ' ';
        file += std::to_string(image_height) + "\n255\n";
        raytracer::Scene scene = room();
        scene.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(5 * i + 50 ,90,190), 90, glass));
        for (int j = image_height-1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << image_height - j - 1 << " / " << image_height << " [" << i << " / " << time * fps << "]" <<' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                Math::Color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_double()) / (image_width-1);
                    auto v = (j + random_double()) / (image_height-1);
                    raytracer::Ray r = cam.getRay(u, v);
                    pixel_color += scene.rayColor(r, background, std::make_shared<raytracer::Scene>(lights), depth);
                }
                raytracer::Scene::writePixel(file, pixel_color, samples_per_pixel);
            }
        }
        ppm_buffer.push_back(file);
    }

    raytracer::GifCreator::createGif("jej.gif", ppm_buffer, fps);

    #endif

    return 0;
}
