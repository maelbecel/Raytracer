/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "Ray.hpp"
    #include "Point3D.hpp"
    #include <iostream>

    namespace RayTracer {
        class Sphere {
            public:
                Sphere(): Center(), Radius(0) {};
                Sphere(Math::Point3D center, double radius): Center(center), Radius(radius) {}
                Sphere(const Sphere &other): Center(other.Center), Radius(other.Radius) {}
                ~Sphere() = default;

                bool hits(RayTracer::Ray ray) {
                    Math::Point3D point = ray.Origin - Center;
                    Math::Vector3D oc(point.X, point.Y, point.Z);
                    double a = ray.Direction.dot(ray.Direction);
                    double b = 2.0 * oc.dot(ray.Direction);
                    double c = oc.dot(oc) - Radius * Radius;
                    double discriminant = b * b - 4 * a * c;
                    return (discriminant > 0);
                }

                Math::Point3D Center;
                double Radius;
            protected:
            private:
        };
    }

#endif /* !SPHERE_HPP_ */
