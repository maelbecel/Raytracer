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
                Vector3D();
                Vector3D(double x, double y, double z);
                Vector3D(const Vector3D &other);

                ~Vector3D() = default;

                Vector3D &operator=(const Vector3D &other);
                Vector3D &operator+(const Vector3D &other);
                Vector3D &operator-(const Vector3D &other);
                Vector3D &operator*(const Vector3D &other);
                Vector3D &operator/(const Vector3D &other);
                Vector3D &operator+=(const Vector3D &other);
                Vector3D &operator-=(const Vector3D &other);
                Vector3D &operator*=(const Vector3D &other);
                Vector3D &operator/=(const Vector3D &other);
                Vector3D &operator*(double x);
                Vector3D &operator/(double x);
                Vector3D &operator*=(double x);
                Vector3D &operator/=(double x);
                Vector3D &operator=(const Point3D &other);


                double length(void);
                double dot(const Vector3D &other);
                double dot(const Point3D &point);
                Vector3D cross(const Vector3D &other);
                Point3D cross(const Point3D &point);

                double X;
                double Y;
                double Z;

            protected:
            private:
        };
    }

#endif /* !VECTOR3D_HPP_ */
