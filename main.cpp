/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** main
*/

#include "Camera.hpp"
#include "Scene.hpp"

int main ()
{
    raytracer::Scene scene;
    std::shared_ptr<raytracer::Camera> camera = std::make_shared<raytracer::Camera>();
    scene.addCamera(camera);
    std::shared_ptr<raytracer::Object> object = std::make_shared<raytracer::Object>();
    std::shared_ptr<raytracer::Sphere> sphere = std::make_shared<raytracer::Sphere>(Math::Point3D(0, 0, 1), 0.2);
    std::shared_ptr<raytracer::Object> object2 = std::make_shared<raytracer::Object>();
    std::shared_ptr<raytracer::Object> object3 = std::make_shared<raytracer::Object>();
    std::shared_ptr<raytracer::Object> object4 = std::make_shared<raytracer::Object>();
    std::shared_ptr<raytracer::Sphere> sphere2 = std::make_shared<raytracer::Sphere>(Math::Point3D(0.4, 0, 1), 0.2);
    std::shared_ptr<raytracer::Sphere> sphere3 = std::make_shared<raytracer::Sphere>(Math::Point3D(0, 0.4, 1), 0.2);
    std::shared_ptr<raytracer::Triangle> triangle = std::make_shared<raytracer::Triangle>(Math::Point3D(0, 0, 1), Math::Point3D(0.4, 0, 1), Math::Point3D(0, 0.4, 1));
    object4->setShape(triangle);

    object->setShape(sphere);
    object2->setShape(sphere2);
    object3->setShape(sphere3);
    scene.addObject(object4);
    scene.addObject(object);
    scene.addObject(object2);
    scene.addObject(object3);
    scene.render();
}

