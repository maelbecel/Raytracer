/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
    #define VECTOR3D_HPP_

    #include <math.h>
    #include <stdlib.h>
    #include <iostream>
    #include <cmath>

    using std::sqrt;

    #define CLAMP(x, min, max) (x < min) ? min : (x > max) ? max : x
    #define random_double() rand() / (RAND_MAX + 1.0)
    #define random_double_mm(min, max) min + (max - min) * random_double()


    namespace Math {
        class Vector3D;
        class Vector3D {
            public:
                Vector3D() : _x(0), _y(0), _z(0) {}
                Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

                double getX() const { return _x; };
                double getY() const { return _y; };
                double getZ() const { return _z; };

                void setX(double i) {_x = i;};
                void setY(double i) {_y = i;};
                void setZ(double i) {_z = i;};

                Vector3D operator-() const;
                Vector3D &operator+=(const Vector3D &other);
                Vector3D &operator-=(const Vector3D &other);
                Vector3D &operator*=(const double &other);
                Vector3D &operator/=(const double &other);
                Vector3D operator+(const Vector3D &other) const;
                Vector3D operator-(const Vector3D &other) const;
                Vector3D operator*(const double &other) const;
                Vector3D operator*(const Vector3D &other) const;
                Vector3D operator/(const double &other) const;


                double len() const;
                double len_squared() const;
                bool near_zero() const;
                double dot(const Vector3D &other) const;
                Vector3D cross(const Vector3D &other) const;
                Vector3D unit_vector() const;

                static Vector3D random_in_unit_sphere();
                static Vector3D random_unit_vector();
                static Vector3D random_in_hemisphere(const Vector3D &normal);
                static Vector3D reflect(const Vector3D &v, const Vector3D &n);
                static Vector3D refract(const Vector3D &uv, const Vector3D &n, double etai_over_etat);
                static Vector3D random_in_unit_disk();
                static Vector3D random();
                static Vector3D random(double min, double max);



            private:
                double _x;
                double _y;
                double _z;
        };
        using Color = Vector3D;

        inline std::ostream &operator<<(std::ostream &out, const Vector3D &v)
        {
            return out << v.getX() << ' ' << v.getY() << ' ' << v.getZ();
        }

        inline Vector3D operator*(double t, Vector3D v)
        {
            return Vector3D(t * v.getX(), t * v.getY(), t * v.getZ());
        }
    }

#endif /* !VECTOR3D_HPP_ */
