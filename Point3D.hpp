/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
    #define POINT3D_HPP_

    #include "Vector3D.hpp"

    namespace Math {
        class Point3D {
            public:
                Point3D(): X(0), Y(0), Z(0) {};
                Point3D(double x, double y, double z): X(x), Y(y), Z(z) {}
                Point3D(const Point3D &other): X(other.X), Y(other.Y), Z(other.Z) {}
                Point3D &operator=(const Point3D &other) {
                    X = other.X;
                    Y = other.Y;
                    Z = other.Z;
                    return *this;
                }

                Point3D &operator+(const Vector3D &other) {
                    X += other.X;
                    Y += other.Y;
                    Z += other.Z;
                    return *this;
                }

                Point3D &operator-(const Vector3D &other) {
                    X -= other.X;
                    Y -= other.Y;
                    Z -= other.Z;
                    return *this;
                }

                Point3D &operator-(const Point3D &other) {
                    X -= other.X;
                    Y -= other.Y;
                    Z -= other.Z;
                    return *this;
                }

                ~Point3D() = default;

                double X;
                double Y;
                double Z;

            protected:
            private:
        };
    }

#endif /* !POINT3D_HPP_ */
