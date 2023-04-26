/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Point3D
*/

#include "Point3D.hpp"

namespace Math {
    Point3D::Point3D(): X(0), Y(0), Z(0) {};

    Point3D::Point3D(double x, double y, double z): X(x), Y(y), Z(z) {};

    Point3D::Point3D(const Point3D &other): X(other.X), Y(other.Y), Z(other.Z) {};

    Point3D &Point3D::operator=(const Point3D &other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    Point3D &Point3D::operator+(const Vector3D &other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Point3D &Point3D::operator-(const Vector3D &other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Point3D &Point3D::operator-(const Point3D &other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3D Point3D::sub(const Point3D &other)
    {
        return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    double Point3D::dot(const Point3D &other)
    {
        return X * other.X + Y * other.Y + Z * other.Z;
    }

    double Point3D::dot(const Vector3D &vector)
    {
        return X * vector.X + Y * vector.Y + Z * vector.Z;
    }

    Point3D Point3D::cross(const Point3D &other)
    {
        return Point3D(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X);
    }
}
