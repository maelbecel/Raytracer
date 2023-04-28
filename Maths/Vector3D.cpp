/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Vector3D
*/

#include "Vector3D.hpp"

namespace Math {
    Vector3D Vector3D::operator-() const
    {
        return Vector3D(-_x, -_y, -_z);
    }

    Vector3D &Vector3D::operator+=(const Vector3D &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    Vector3D &Vector3D::operator-=(const Vector3D &other)
    {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    Vector3D &Vector3D::operator*=(const double &other)
    {
        _x *= other;
        _y *= other;
        _z *= other;
        return *this;
    }

    Vector3D &Vector3D::operator/=(const double &other)
    {
        _x /= other;
        _y /= other;
        _z /= other;
        return *this;
    }

    Vector3D Vector3D::operator+(const Vector3D &other) const
    {
        return Vector3D(_x + other._x, _y + other._y, _z + other._z);
    }

    Vector3D Vector3D::operator-(const Vector3D &other) const
    {
        return Vector3D(_x - other._x, _y - other._y, _z - other._z);
    }

    Vector3D Vector3D::operator*(const double &other) const
    {
        return Vector3D(_x * other, _y * other, _z * other);
    }

    Vector3D Vector3D::operator*(const Vector3D &other) const
    {
        return Vector3D(_x * other._x, _y * other._y, _z * other._z);
    }

    Vector3D Vector3D::operator/(const double &other) const
    {
        return Vector3D(_x / other, _y / other, _z / other);
    }

    double Vector3D::len_squared() const
    {
        return _x * _x + _y * _y + _z * _z;
    }

    double Vector3D::len() const
    {
        return sqrt(len_squared());
    }

    Vector3D Vector3D::random()
    {
        return Vector3D(random_double(), random_double(), random_double());
    }

    Vector3D Vector3D::random(double min, double max)
    {
        return Vector3D(random_double_mm(min, max), random_double_mm(min, max), random_double_mm(min, max));
    }

    bool Vector3D::near_zero() const
    {
        const auto s = 1e-8;
        return (fabs(_x) < s) && (fabs(_y) < s) && (fabs(_z) < s);
    }

    double Vector3D::dot(const Vector3D &other) const
    {
        return _x * other._x + _y * other._y + _z * other._z;
    }

    Vector3D Vector3D::cross(const Vector3D &other) const
    {
        return Vector3D(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
    }

    Vector3D Vector3D::unit_vector() const
    {
        return *this / len();
    }

    Vector3D Vector3D::random_in_unit_sphere()
    {
        while (true) {
            auto p = Vector3D::random(-1, 1);
            if (p.len_squared() >= 1)
                continue;
            return p;
        }
    }

    Vector3D Vector3D::random_unit_vector()
    {
        return random_in_unit_sphere().unit_vector();
    }

    Vector3D Vector3D::random_in_hemisphere(const Vector3D &normal)
    {
        Vector3D in_unit_sphere = random_in_unit_sphere();
        if (in_unit_sphere.dot(normal) > 0.0)
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }

    Vector3D Vector3D::random_in_unit_disk()
    {
        while (true) {
            auto p = Vector3D(random_double_mm(-1, 1), random_double_mm(-1, 1), 0);
            if (p.len_squared() >= 1)
                continue;
            return p;
        }
    }

    Vector3D Vector3D::reflect(const Vector3D &v, const Vector3D &n)
    {
        return v - 2 * v.dot(n) * n;
    }

    Vector3D Vector3D::refract(const Vector3D &uv, const Vector3D &n, double etai_over_etat)
    {
        auto cos_theta = fmin(-uv.dot(n), 1.0);
        Vector3D r_out_perp = etai_over_etat * (uv + cos_theta * n);
        Vector3D r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.len_squared())) * n;
        return r_out_perp + r_out_parallel;
    }

}
