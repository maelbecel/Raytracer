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

    std::shared_ptr<raytracer::Triangle> triangle = std::make_shared<raytracer::Triangle>(Math::Point3D(0, 0, 0.5), Math::Point3D(0.25, 0.25, 1), Math::Point3D(-0.25, 0.25, 1));
    std::shared_ptr<raytracer::Object> object = std::make_shared<raytracer::Object>();
    object->setShape(triangle);
    object->setColor(raytracer::Color(255, 0, 0));
    scene.addObject(object);

    std::shared_ptr<raytracer::Triangle> triangle2 = std::make_shared<raytracer::Triangle>(Math::Point3D(0, 0, 0.5), Math::Point3D(0.25, -0.25, 1), Math::Point3D(-0.25, -0.25, 1));
    std::shared_ptr<raytracer::Object> object2 = std::make_shared<raytracer::Object>();
    object2->setShape(triangle2);
    object2->setColor(raytracer::Color(0, 255, 0));
    scene.addObject(object2);

    std::shared_ptr<raytracer::Triangle> triangle3 = std::make_shared<raytracer::Triangle>(Math::Point3D(0, 0, 0.5), Math::Point3D(0.25, -0.25, 1), Math::Point3D(0.25, 0.25, 1));
    std::shared_ptr<raytracer::Object> object3 = std::make_shared<raytracer::Object>();
    object3->setShape(triangle3);
    object3->setColor(raytracer::Color(0, 0, 255));
    scene.addObject(object3);

    std::shared_ptr<raytracer::Triangle> triangle4 = std::make_shared<raytracer::Triangle>(Math::Point3D(0, 0, 0.5), Math::Point3D(-0.25, -0.25, 1), Math::Point3D(-0.25, 0.25, 1));
    std::shared_ptr<raytracer::Object> object4 = std::make_shared<raytracer::Object>();
    object4->setShape(triangle4);
    object4->setColor(raytracer::Color(255, 255, 0));
    scene.addObject(object4);

    std::shared_ptr<raytracer::Ambiant> ambiant = std::make_shared<raytracer::Ambiant>(Math::Point3D(1, 0, 0));
    scene.addLight(ambiant);

    scene.render();
}

