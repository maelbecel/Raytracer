/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
    #define RECTANGLE_HPP_

    #include "../Maths/Point3D.hpp"
    #include "../Ray.hpp"
    #include "IShape.hpp"

    namespace raytracer {
        class Rectangle3D : public IShape {
            public:
                Rectangle3D();
                Rectangle3D(Math::Point3D origin, Math::Vector3D bottom_side, Math::Vector3D left_side);
                Rectangle3D(const Rectangle3D &other): origin(other.origin), bottom_side(other.bottom_side), left_side(other.left_side) {}
                Rectangle3D &operator=(const Rectangle3D &other);
                ~Rectangle3D() {};

                Math::Point3D origin;
                Math::Vector3D bottom_side;
                Math::Vector3D left_side;

                Math::Point3D pointAt(double u, double v);

                bool hits(UNUSED raytracer::Ray ray);

            protected:
            private:
        };
    }

#endif /* !RECTANGLE_HPP_ */
