/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

namespace raytracer {
    Ray::Ray(): Origin(), Direction() {};

    Ray::Ray(Math::Vector3D origin, Math::Vector3D direction, double time): Origin(origin), Direction(direction), tm(time) {}

    Ray::Ray(const Ray &other): Origin(other.Origin), Direction(other.Direction) {}

    Ray &Ray::operator=(const Ray &other) {
        Origin = other.Origin;
        Direction = other.Direction;
        return *this;
    }

    Math::Vector3D Ray::at(double x) const { return Origin + x * Direction;};

}
