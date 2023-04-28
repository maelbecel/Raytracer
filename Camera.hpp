/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "./Maths/Vector3D.hpp"
    #include "Ray.hpp"

    namespace raytracer {
        class Camera {
            public:
                Camera() {};
                Camera(Math::Vector3D from, Math::Vector3D at, Math::Vector3D vup, double vfov, double ratio, double aperture, double focus);
                Ray getRay(double s, double t) const;
                ~Camera() = default;
            private:
                Math::Vector3D _origin;
                Math::Vector3D _lower_left_corner;
                Math::Vector3D _horizontal;
                Math::Vector3D _vertical;
                Math::Vector3D _u, _v, _w;
                double _lens_radius;
        };
    }

#endif /* !CAMERA_HPP_ */
