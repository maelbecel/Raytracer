/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
    #define VECTOR3D_HPP_

    #include <math.h>

    namespace Math {
        class Point3D;
        class Vector3D {
            public:
                Vector3D(): X(0), Y(0), Z(0) {};
                Vector3D(double x, double y, double z): X(x), Y(y), Z(z) {}
                Vector3D(const Vector3D &other): X(other.X), Y(other.Y), Z(other.Z) {}
                Vector3D &operator=(const Vector3D &other) {
                    X = other.X;
                    Y = other.Y;
                    Z = other.Z;
                    return *this;
                }
                Vector3D &operator+(const Vector3D &other) {
                    X += other.X;
                    Y += other.Y;
                    Z += other.Z;
                    return *this;
                }
                Vector3D &operator-(const Vector3D &other) {
                    X -= other.X;
                    Y -= other.Y;
                    Z -= other.Z;
                    return *this;
                }
                Vector3D &operator*(const Vector3D &other) {
                    X *= other.X;
                    Y *= other.Y;
                    Z *= other.Z;
                    return *this;
                }
                Vector3D &operator/(const Vector3D &other) {
                    X /= other.X;
                    Y /= other.Y;
                    Z /= other.Z;
                    return *this;
                }
                Vector3D &operator+=(const Vector3D &other) {
                    X += other.X;
                    Y += other.Y;
                    Z += other.Z;
                    return *this;
                }
                Vector3D &operator-=(const Vector3D &other) {
                    X -= other.X;
                    Y -= other.Y;
                    Z -= other.Z;
                    return *this;
                }
                Vector3D &operator*=(const Vector3D &other) {
                    X *= other.X;
                    Y *= other.Y;
                    Z *= other.Z;
                    return *this;
                }
                Vector3D &operator/=(const Vector3D &other) {
                    X /= other.X;
                    Y /= other.Y;
                    Z /= other.Z;
                    return *this;
                }
                Vector3D &operator*(double x) {
                    X *= x;
                    Y *= x;
                    Z *= x;
                    return *this;
                }
                Vector3D &operator/(double x) {
                    X /= x;
                    Y /= x;
                    Z /= x;
                    return *this;
                }
                Vector3D &operator*=(double x) {
                    X *= x;
                    Y *= x;
                    Z *= x;
                    return *this;
                }
                Vector3D &operator/=(double x) {
                    X /= x;
                    Y /= x;
                    Z /= x;
                    return *this;
                }
                Vector3D &operator=(const Point3D &other);

                ~Vector3D() = default;

                double length(void) {
                    return sqrt(X * X + Y * Y + Z * Z);
                }

                double dot(const Vector3D &other) {
                    return X * other.X + Y * other.Y + Z * other.Z;
                }

                double X;
                double Y;
                double Z;

            protected:
            private:
        };
    }

#endif /* !VECTOR3D_HPP_ */
