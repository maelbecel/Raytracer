/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Triangle
*/

#include "Triangle.hpp"

namespace raytracer {

    Triangle::Triangle(): A(), B(), C() {};
    Triangle::Triangle(Math::Point3D a, Math::Point3D b, Math::Point3D c): A(a), B(b), C(c) {}
    Triangle::Triangle(const Triangle &other): A(other.A), B(other.B), C(other.C) {};

    Triangle &Triangle::operator=(const Triangle &other) {
        A = other.A;
        B = other.B;
        C = other.C;
        return *this;
    }

    bool Triangle::hits(raytracer::Ray ray)
    {
        const double EPSILON = 0.0000001;

        Math::Vector3D edge1 = B.sub(A);
        Math::Vector3D edge2 = C.sub(A);
        Math::Vector3D h = ray.Direction.cross(edge2);
        double a = edge1.dot(h);

        if (a > -EPSILON && a < EPSILON)
            return false;

        double f = 1.0 / a;
        Math::Vector3D s = ray.Origin.sub(A);
        double u = f * s.dot(h);

        if (u < 0.0 || u > 1.0)
            return false;

        Math::Vector3D q = s.cross(edge1);
        double v = f * ray.Direction.dot(q);

        if (v < 0.0 || u + v > 1.0) {
            return false;
        }

        double t = f * edge2.dot(q);
        return (t > EPSILON);
    }

    Math::Vector3D Triangle::getNormal(Math::Point3D point)
    {
        Math::Point3D center = {
            (A.X + B.X + C.X) / 3,
            (A.Y + B.Y + C.Y) / 3,
            (A.Z + B.Z + C.Z) / 3
        };
        Math::Vector3D normal = {
            point.X - center.X,
            point.Y - center.Y,
            point.Z - center.Z
        };
        return normal;
    }
}
