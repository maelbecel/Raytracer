/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace Math {
    Vector3D &Vector3D::operator=(const Point3D &other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }
}
