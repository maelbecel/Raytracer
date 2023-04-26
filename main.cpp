/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** main
*/

#include "Camera.hpp"
#include "Scene.hpp"
#include "./Shapes/Sphere.hpp"
#include "./Shapes/Triangle.hpp"
#include "./Maths/Point3D.hpp"
#include <iostream>
#include <fstream>
#include "Object.hpp"

void get_ray(std::ofstream& file, raytracer::Scene scene, raytracer::Ray r)
{
    int x = 1;
    for (std::shared_ptr<raytracer::Object> object : scene.getObjects()) {
        std::cout << "Check for object " << x -1 << std::endl;
        if (object->getShape() == nullptr)
            std::cout << "Object " << x -1 << " has no shape" << std::endl;
        if (object->getShape()->hits(r)) {
            file << x * 50 << " " << x * 50 << " " << x * 50 << std::endl;
            return;
        }
        x++;
    }
    file << "0 0 0" << std::endl;
}

int main ()
{
    std::ofstream file("image.ppm");
    file << "P3" << std::endl << "400 400" << std::endl << "255" << std::endl;
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
    for (double i = -200 ; i < 200 ; i += 1) {
        for (double j = -200 ; j < 200 ; j += 1) {
            double u = j / 400 ;
            double v = i / 400 ;
            raytracer::Ray r = camera->ray(u, v);
            get_ray(file, scene, r);
        }
    }
}

