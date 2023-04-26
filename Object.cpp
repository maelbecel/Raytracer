/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Object
*/

#include "Object.hpp"

namespace raytracer {
    Object::Object(std::shared_ptr<IShape> shape = nullptr, std::shared_ptr<IMaterial> _material = nullptr) : _shape(shape), _material(_material) {};

    Math::Vector3D Object::getNormal(Math::Point3D point)
    {
        return _shape->getNormal(point);
    }
}


