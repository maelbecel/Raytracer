/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** main
*/

#include "Camera.hpp"
#include "Scene.hpp"
#include "./Shapes/Sphere.hpp"
#include "./Maths/Point3D.hpp"
#include <iostream>
#include <fstream>
#include "Object.hpp"

int main ()
{
    int x = 0;
    std::ofstream file("image.ppm");
    file << "P3" << std::endl << "400 400" << std::endl << "255" << std::endl;
    raytracer::Scene scene;
    std::shared_ptr<raytracer::Camera> camera = std::make_shared<raytracer::Camera>();
    scene.addCamera(camera);
    std::shared_ptr<raytracer::Object> object = std::make_shared<raytracer::Object>();
    std::shared_ptr<raytracer::Sphere> sphere = std::make_shared<raytracer::Sphere>(Math::Point3D(0, 0, 1.5), 0.2);
    object->setShape(sphere);
    scene.addObject(object);
    for (double i = -200 ; i < 200 ; i += 1) {
        for (double j = -200 ; j < 200 ; j += 1) {
            double u = j / 400 ;
            double v = i / 400 ;
            raytracer::Ray r = camera->ray(u, v);
            for (std::shared_ptr<raytracer::Object> object : scene.getObjects()) {
                if (object->getShape()->hits(r)) {
                    file << x * 50 << " " << x * 50 << " " << x * 50 << std::endl;
                    x++;
                } else {
                    file << "0 0 0" << std::endl;
                }
            }
        }
    }
}

