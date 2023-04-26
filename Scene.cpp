/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

namespace raytracer {

    void Scene::get_ray(raytracer::Ray r)
    {
        int x = 1;
        for (std::shared_ptr<raytracer::Object> object : this->getObjects()) {
            if (object->getShape() == nullptr)
                std::cout << "Object " << x -1 << " has no shape" << std::endl;
            else if (object->getShape()->hits(r)) {
                _file << x * 50 << " " << x * 50 << " " << x * 50 << std::endl;
                return;
            }
            x++;
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
                get_ray(r);
            }
        }
    }
}
