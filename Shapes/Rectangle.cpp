/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#include "Rectangle.hpp"
#include "../Maths/Vector3D.hpp"

namespace raytracer {
    Rectangle3D::Rectangle3D() : origin(), bottom_side(), left_side() {};
    Rectangle3D::Rectangle3D(Math::Point3D origin, Math::Vector3D bottom_side, Math::Vector3D left_side): origin(origin), bottom_side(bottom_side), left_side(left_side) {};
    Rectangle3D::Rectangle3D(const Rectangle3D &other): origin(other.origin), bottom_side(other.bottom_side), left_side(other.left_side) {};


    Rectangle3D &Rectangle3D::operator=(const Rectangle3D &other) {
        origin = other.origin;
        bottom_side = other.bottom_side;
        left_side = other.left_side;
        return *this;
    }

    Math::Point3D Rectangle3D::pointAt(double u, double v)
    {
        return {
            origin.X + u * bottom_side.X + v * left_side.X,
            origin.Y + u * bottom_side.Y + v * left_side.Y,
            origin.Z + u * bottom_side.Z + v * left_side.Z
        };
    }

    bool Rectangle3D::hits(UNUSED raytracer::Ray ray)
    {
        return false;
    }
}