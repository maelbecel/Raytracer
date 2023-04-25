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

    bool Triangle::hits(UNUSED raytracer::Ray ray) { return false; };

}
