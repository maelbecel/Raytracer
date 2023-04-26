/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace Math {
    Vector3D::Vector3D(): X(0), Y(0), Z(0) {};
    Vector3D::Vector3D(double x, double y, double z): X(x), Y(y), Z(z) {}
    Vector3D::Vector3D(const Vector3D &other): X(other.X), Y(other.Y), Z(other.Z) {}

    Vector3D &Vector3D::operator=(const Vector3D &other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator+(const Vector3D &other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator-(const Vector3D &other) {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator*(const Vector3D &other) {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator/(const Vector3D &other) {
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator+=(const Vector3D &other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator-=(const Vector3D &other) {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator*=(const Vector3D &other) {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator/=(const Vector3D &other) {
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        return *this;
    }

    Vector3D &Vector3D::operator*(double x) {
        X *= x;
        Y *= x;
        Z *= x;
        return *this;
    }

    Vector3D &Vector3D::operator/(double x) {
        X /= x;
        Y /= x;
        Z /= x;
        return *this;
    }

    Vector3D &Vector3D::operator*=(double x) {
        X *= x;
        Y *= x;
        Z *= x;
        return *this;
    }

    Vector3D &Vector3D::operator/=(double x) {
        X /= x;
        Y /= x;
        Z /= x;
        return *this;
    }

    Vector3D &Vector3D::operator=(const Point3D &other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    double Vector3D::length(void) {
        return sqrt(X * X + Y * Y + Z * Z);
    }

    double Vector3D::dot(const Vector3D &other) {
        return X * other.X + Y * other.Y + Z * other.Z;
    }

    double Vector3D::dot(const Point3D &point) {
        return X * point.X + Y * point.Y + Z * point.Z;
    }

    Vector3D Vector3D::cross(const Vector3D &other) {
        return Vector3D(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X);
    }

    Point3D Vector3D::cross(const Point3D &point) {
        return Point3D(Y * point.Z - Z * point.Y, Z * point.X - X * point.Z, X * point.Y - Y * point.X);
    }
}
