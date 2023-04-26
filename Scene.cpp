/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

namespace raytracer {

    void Scene::get_ray(raytracer::Ray r, Math::Point3D point)
    {
        for (std::shared_ptr<raytracer::Object> object : this->getObjects()) {
            if (object->getShape() == nullptr)
                std::cerr << "Object has no shape" << std::endl;
            else if (object->getShape()->hits(r)) {
                Math::Vector3D normal = object->getShape()->getNormal(point);
                Math::Vector3D lightDir = _lights[0]->getLightVector(point);
                double dot = normal.dot(lightDir);
                if (dot < 0)
                    dot = 0;
                _file << (int)(object->getColor().R * dot) << " " << (int)(object->getColor().G * dot) << " " << (int)(object->getColor().B * dot) << std::endl;
                return;
            }
        }
        _file << "0 0 0" << std::endl;
    }

    void Scene::render() {
        _file << "P3" << std::endl << WIDTH << " " << HEIGHT << std::endl << "255" << std::endl;
        for (double i = -(HEIGHT/2) ; i < (HEIGHT/2) ; i += 1) {
            for (double j = -(WIDTH/2) ; j < (WIDTH/2) ; j += 1) {
                double u = j / WIDTH ;
                double v = i / HEIGHT ;
                raytracer::Ray r = _camera->ray(u, v);
                get_ray(r, _camera->screen.pointAt(u, v));
            }
        }
    }
}
