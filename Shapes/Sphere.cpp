/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace raytracer {
    Sphere::Sphere(): Center(), Radius(0) {};
    Sphere::Sphere(Math::Point3D center, double radius): Center(center), Radius(radius) {}
    Sphere::Sphere(const Sphere &other): Center(other.Center), Radius(other.Radius) {}

    bool Sphere::hits(raytracer::Ray ray)
    {
        Math::Point3D point = ray.Origin - Center;
        Math::Vector3D oc(point.X, point.Y, point.Z);
        double a = ray.Direction.dot(ray.Direction);
        double b = 2.0 * oc.dot(ray.Direction);
        double c = oc.dot(oc) - Radius * Radius;
        double discriminant = b * b - 4 * a * c;
        return (discriminant > 0);
    };
}
