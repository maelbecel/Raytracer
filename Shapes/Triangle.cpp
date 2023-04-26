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
        Math::Point3D edge1 = B - A;
        Math::Point3D edge2 = C - A;
        Math::Point3D h = ray.Direction.cross(edge2);
        double a = edge1.dot(h);
        if (a > -0.00001 && a < 0.00001)
            return false;
        double f = 1 / a;
        Math::Point3D s = ray.Origin - A;
        double u = f * s.dot(h);
        if (u < 0.0 || u > 1.0)
            return false;
        Math::Point3D q = s.cross(edge1);
        double v = f * ray.Direction.dot(q);
        if (v < 0.0 || u + v > 1.0)
            return false;
        double t = f * edge2.dot(q);
        if (t > 0.00001)
            return true;
        else
            return false;
    }

}
