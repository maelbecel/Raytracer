/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Orthonormal
*/

#ifndef ORTHONORMAL_HPP_
    #define ORTHONORMAL_HPP_

    #include "Vector3D.hpp"

    namespace Math {
        class Orthonormal {
            public:
                Orthonormal() {}

                inline Math::Vector3D operator[](int i) const { return _axis[i];}

                Math::Vector3D u() const { return _axis[0];}
                Math::Vector3D v() const { return _axis[1];}
                Math::Vector3D w() const { return _axis[2];}

                Math::Vector3D local(double a, double b, double c) const
                {
                    return a * u() + b * v() + c * w();
                }

                Math::Vector3D local(const Math::Vector3D &a) const
                {
                    return a.getX() * u() + a.getY() * v() + a.getZ() * w();
                }

                void build_from_w(const Math::Vector3D &vec)
                {
                    _axis[2] = vec.unit_vector();
                    Math::Vector3D a = (fabs(w().getX()) > 0.9) ? Math::Vector3D(0, 1, 0) : Math::Vector3D(1, 0, 0);
                    _axis[1] = w().cross(a).unit_vector();
                    _axis[0] = w().cross(v());
                }

                static Math::Vector3D random_cosine_direction() {
                    double r1 = random_double();
                    double r2 = random_double();
                    double z = sqrt(1 - r2);
                    double phi = 2 * M_PI * r1;
                    double x = cos(phi) * sqrt(r2);
                    double y = sin(phi) * sqrt(r2);
                    return Math::Vector3D(x, y, z);
                }





            protected:
            private:
                Math::Vector3D _axis[3];
        };
    }

#endif /* !ORTHONORMAL_HPP_ */
