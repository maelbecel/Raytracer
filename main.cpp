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
#include "Shapes/ZRotation.hpp"
#include "Shapes/XRotation.hpp"
#include "Shapes/DirectionnalLight.hpp"
#include "Texture/Checker.hpp"
#include "Texture/Noise.hpp"
#include "Texture/Image.hpp"
#include "Parser/Builder.hpp"
#include "Shapes/Triangle.hpp"
#include "Shapes/Plan.hpp"
#include "Shapes/AmbientLight.hpp"

raytracer::Scene final_scene()
{
    raytracer::Scene objects;

    auto red   = std::make_shared<raytracer::Lambertian>(Math::Color(.65, .05, .05));
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(.73, .73, .73));
    auto green = std::make_shared<raytracer::Lambertian>(Math::Color(.12, .45, .15));
    auto light = std::make_shared<raytracer::DiffuseLight>(Math::Color(15, 15, 15));

    auto metal = std::make_shared<raytracer::Metal>(Math::Color(.8, .85, .88), 0);
    auto blue = std::make_shared<raytracer::Lambertian>(Math::Color(.3, .2, .7));
    std::shared_ptr<raytracer::IShape> box1 = std::make_shared<raytracer::Box>(Math::Vector3D(50,0,500), Math::Vector3D(150,300,350), blue);
    objects.addObject(box1);

    auto glass = std::make_shared<raytracer::Dielectric>(1.5);
    objects.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(190,90,190), 90, glass));

    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 555, green));
    objects.addObject(std::make_shared<raytracer::YZRectangle>(0, 555, 0, 555, 0, red));
    objects.addObject(std::make_shared<raytracer::DirectionnalLight>(std::make_shared<raytracer::XZRectangle>(213, 343, 227, 332, 554, light)));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 555, white));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 0, white));
    objects.addObject(std::make_shared<raytracer::XYRectangle>(0, 555, 0, 555, 555, white));


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
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 555, white));
    objects.addObject(std::make_shared<raytracer::XZRectangle>(0, 555, 0, 555, 0, white));
    objects.addObject(std::make_shared<raytracer::XYRectangle>(0, 555, 0, 555, 555, white));

    auto metal = std::make_shared<raytracer::Metal>(Math::Color(.89, .75, .78), 0);
    auto blue = std::make_shared<raytracer::Lambertian>(Math::Color(.3, .2, .7));
    std::shared_ptr<raytracer::IShape> box1 = std::make_shared<raytracer::Box>(Math::Vector3D(50,0,500), Math::Vector3D(150,300,350), blue);
    objects.addObject(box1);

    return objects;
}

int main ()
{
    // Builder

    Builder::Builder builder("scene.cfg");
    raytracer::Scene world = final_scene();
    raytracer::Scene lights;
    auto white = std::make_shared<raytracer::Lambertian>(Math::Color(0, 0,0));

    lights.addObject(std::make_shared<raytracer::XZRectangle>(213, 343, 227, 332, 554, white));
    lights.addObject(std::make_shared<raytracer::Sphere>(Math::Vector3D(190, 90, 190), 90, white));

    // Image

    world.ppmRenderer(builder, lights);
    world.gifRenderer(builder, lights);

    return 0;
}
