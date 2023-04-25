/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "./Maths/Point3D.hpp"
    #include "./Shapes/Rectangle.hpp"
    #include "Ray.hpp"

    namespace raytracer {
        class Camera {
            public:
                Camera(): origin() {
                    screen = {
                        {0, 0, 1},
                        {1, 0, 0},
                        {0, 1, 0}
                    };
                };
                ~Camera() = default;

                Math::Point3D origin;
                Rectangle3D screen;

                Ray ray(double u, double v)
                {
                    return {
                        origin,
                        {
                            screen.pointAt(u, v).X - origin.X,
                            screen.pointAt(u, v).Y - origin.Y,
                            screen.pointAt(u, v).Z - origin.Z
                        }
                    };
                }
            protected:
            private:
        };
    }

#endif /* !CAMERA_HPP_ */
