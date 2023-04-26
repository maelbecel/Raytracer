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
                Point3D();
                Point3D(double x, double y, double z);
                Point3D(const Point3D &other);

                ~Point3D() = default;

                Point3D &operator=(const Point3D &other);
                Point3D &operator+(const Vector3D &other);
                Point3D &operator-(const Vector3D &other);
                Point3D &operator-(const Point3D &other);

                double dot(const Point3D &other);
                Point3D cross(const Point3D &other);

                double X;
                double Y;
                double Z;

            protected:
            private:
        };
    }

#endif /* !POINT3D_HPP_ */
