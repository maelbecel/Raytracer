/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
    #define RECTANGLE_HPP_

    #include "Point3D.hpp"

    namespace RayTracer {
        class Rectangle3D {
            public:
                Rectangle3D(): origin(), bottom_side(), left_side() {};
                Rectangle3D(Math::Point3D origin, Math::Vector3D bottom_side, Math::Vector3D left_side): origin(origin), bottom_side(bottom_side), left_side(left_side) {}
                Rectangle3D(const Rectangle3D &other): origin(other.origin), bottom_side(other.bottom_side), left_side(other.left_side) {}
                Rectangle3D &operator=(const Rectangle3D &other) {
                    origin = other.origin;
                    bottom_side = other.bottom_side;
                    left_side = other.left_side;
                    return *this;
                }
                ~Rectangle3D() = default;

                Math::Point3D origin;
                Math::Vector3D bottom_side;
                Math::Vector3D left_side;

                Math::Point3D pointAt(double u, double v)
                {
                    return {
                        origin.X + u * bottom_side.X + v * left_side.X,
                        origin.Y + u * bottom_side.Y + v * left_side.Y,
                        origin.Z + u * bottom_side.Z + v * left_side.Z
                    };
                }

            protected:
            private:
        };
    }

#endif /* !RECTANGLE_HPP_ */
