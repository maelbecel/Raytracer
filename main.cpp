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

raytracer::Scene randomScene(void)
{
    raytracer::Scene world;

    auto checker = std::make_shared<raytracer::Checker>(Math::Color(0.2, 0.3, 0.1), Math::Color(0.9, 0.9, 0.9));
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, -1000, 0), 1000, std::make_shared<raytracer::Lambertian>(checker)));


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

raytracer::Scene two_sphere()
{
    raytracer::Scene world;

    auto checker = std::make_shared<raytracer::Checker>(Math::Color(0.2, 0.3, 0.1), Math::Color(0.9, 0.9, 0.9));
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, -10, 0), 10, std::make_shared<raytracer::Lambertian>(checker)));
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, 10, 0), 10, std::make_shared<raytracer::Lambertian>(checker)));
    return world;
}

raytracer::Scene two_perlin_sphere()
{
    raytracer::Scene world;

    auto pertext = std::make_shared<raytracer::Noise>(4);
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, -1000, 0), 1000, std::make_shared<raytracer::Lambertian>(pertext)));
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, 2, 0), 2, std::make_shared<raytracer::Lambertian>(pertext)));

    return world;
}

raytracer::Scene earth()
{
    raytracer::Scene world;
    auto earth_texture = std::make_shared<raytracer::Image>("earthmap.bmp");
    auto earth_surface = std::make_shared<raytracer::Lambertian>(earth_texture);
    auto globe = std::make_shared<raytracer::Sphere>(Math::Vector3D(0,0,0), 2, earth_surface);

    world.addObject(globe);
    return world;
}

raytracer::Scene simple_light()
{
    raytracer::Scene world;

    auto pertext = std::make_shared<raytracer::Noise>(4);
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, -1000, 0), 1000, std::make_shared<raytracer::Lambertian>(pertext)));
    world.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, 2, 0), 2, std::make_shared<raytracer::Lambertian>(pertext)));

    auto diff = std::make_shared<raytracer::DiffuseLight>(Math::Color(4,4,4));
    world.addObject(std::make_shared<raytracer::XYRectangle>(3, 5, 1, 3, -2, diff));

    return world;
}

raytracer::Scene cornell_box()
{
    raytracer::Scene world;
    auto red = std::make_shared<raytracer::Lambertian>(Math::Color(.65, .05, .05));
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(.73, .73, .73));
    auto green = std::make_shared<raytracer::Lambertian>(Math::Color(.12, .45, .15));
    auto light = std::make_shared<raytracer::DiffuseLight>(Math::Color(15, 15, 15));
    auto metal = std::make_shared<raytracer::Metal>(Math::Color(0.5, 0.5, 0.5), 0);

    world.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 555, green));
    world.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 0, red));
    world.addObject(std::make_shared<raytracer::XZRectangle>(213, 343, 227, 332, 554, light));
    world.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 0, white));
    world.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 555, white));
    world.addObject(std::make_shared<raytracer::XYRectangle>(0, 555, 0, 555, 555, white));

    std::shared_ptr<raytracer::IShape> box1 = std::make_shared<raytracer::Box>(Math::Vector3D(0, 0, 0), Math::Vector3D(165, 330, 165), white);
    box1 = std::make_shared<raytracer::YRotation>(box1, 15);
    box1 = std::make_shared<raytracer::Translation>(box1, Math::Vector3D(265, 0, 295));
    world.addObject(box1);
    std::shared_ptr<raytracer::IShape> box2 = std::make_shared<raytracer::Box>(Math::Vector3D(0, 0, 0), Math::Vector3D(165, 165, 165), white);
    box2 = std::make_shared<raytracer::YRotation>(box2, -18);
    box2 = std::make_shared<raytracer::Translation>(box2, Math::Vector3D(130, 0, 65));
    world.addObject(box2);
    return world;
}

raytracer::Scene cornell_smoke()
{
    raytracer::Scene world;
    auto red = std::make_shared<raytracer::Lambertian>(Math::Color(.65, .05, .05));
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(.73, .73, .73));
    auto green = std::make_shared<raytracer::Lambertian>(Math::Color(.12, .45, .15));
    auto light = std::make_shared<raytracer::DiffuseLight>(Math::Color(15, 15, 15));
    auto metal = std::make_shared<raytracer::Metal>(Math::Color(0.5, 0.5, 0.5), 0);

    world.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 555, green));
    world.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 0, red));
    world.addObject(std::make_shared<raytracer::XZRectangle>(213, 343, 227, 332, 554, light));
    world.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 0, white));
    world.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 555, white));
    world.addObject(std::make_shared<raytracer::XYRectangle>(0, 555, 0, 555, 555, white));

    std::shared_ptr<raytracer::IShape> box1 = std::make_shared<raytracer::Box>(Math::Vector3D(0, 0, 0), Math::Vector3D(165, 330, 165), white);
    box1 = std::make_shared<raytracer::YRotation>(box1, 15);
    box1 = std::make_shared<raytracer::Translation>(box1, Math::Vector3D(265, 0, 295));
    box1 = std::make_shared<raytracer::ConstantMedium>(box1, 0.01, Math::Color(0, 0, 0));
    world.addObject(box1);

    std::shared_ptr<raytracer::IShape> box2 = std::make_shared<raytracer::Box>(Math::Vector3D(0, 0, 0), Math::Vector3D(165, 165, 165), white);
    box2 = std::make_shared<raytracer::YRotation>(box2, -18);
    box2 = std::make_shared<raytracer::Translation>(box2, Math::Vector3D(130, 0, 65));
    box2 = std::make_shared<raytracer::ConstantMedium>(box2, 0.01, Math::Color(1, 1, 1));
    world.addObject(box2);
    return world;
}

raytracer::Scene final_scene()
{
    raytracer::Scene boxes1;
    auto ground = std::make_shared<raytracer::Lambertian>(Math::Color(0.48, 0.83, 0.53));

    const int boxes_per_side(20);
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100;
            auto x0 = -1000.0 + i * w;
            auto y0 = 0;
            auto z0 = -1000.0 + j * w;
            auto x1 = x0 + w;
            auto y1 = random_double_mm(1, 101);
            auto z1 = z0 + w;

            boxes1.addObject(std::make_shared<raytracer::Box>(Math::Vector3D(x0, y0, z0), Math::Vector3D(x1, y1, z1), ground));
        }
    }

    raytracer::Scene objects;

    objects.addObject(std::make_shared<raytracer::Node>(boxes1, 0, 1));

    auto light = std::make_shared<raytracer::DiffuseLight>(Math::Color(7, 7, 7));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(123, 423, 147, 412, 554, light));

    auto center1 = Math::Vector3D(400, 400, 200);
    auto center2 = center1 + Math::Vector3D(30, 0, 0);

    auto moving_sphere = std::make_shared<raytracer::Lambertian>(Math::Color(.7, .3, .1));
    objects.addObject(std::make_shared<raytracer::MovingSphere>(center1, center2, 0, 1, 50, moving_sphere));
    objects.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(260, 150, 45), 50, std::make_shared<raytracer::Dielectric>(1.5)));
    objects.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(0, 150, 145), 50, std::make_shared<raytracer::Metal>(Math::Color(.8, .8, .9), 1)));

    auto boundary = std::make_shared<raytracer::Sphere>(Math::Vector3D(360, 150, 145), 70, std::make_shared<raytracer::Dielectric>(1.5));
    objects.addObject(boundary);
    objects.addObject(std::make_shared<raytracer::ConstantMedium>(boundary, .2, Math::Color(.2, .4, .9)));
    boundary = std::make_shared<raytracer::Sphere>(Math::Vector3D(0, 0, 0), 5000, std::make_shared<raytracer::Dielectric>(1.5));
    objects.addObject(std::make_shared<raytracer::ConstantMedium>(boundary, .0001, Math::Color(1, 1, 1)));

    auto pertext = std::make_shared<raytracer::Noise>(0.1);
    objects.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(220, 280, 300), 80, std::make_shared<raytracer::Lambertian>(pertext)));

    raytracer::Scene boxes2;
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++)
        boxes2.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D::random(0, 165), 10, white));

    objects.addObject(std::make_shared<raytracer::Translation>(
                        std::make_shared<raytracer::YRotation>(
                            std::make_shared<raytracer::Node>(boxes2, 0, 1), 15), Math::Vector3D(-100, 270, 395)
                        )
                    );

    return objects;
}

int main ()
{
    // Parser

    Parser::Parser parser("scene.cfg");

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 200;
    const int depth = 4;

    // Scene

    raytracer::Scene world = final_scene();


    // Camera

    Math::Vector3D lookfrom(13,2,3);
    Math::Vector3D lookat(0,0,0);
    Math::Vector3D vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    raytracer::Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

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

