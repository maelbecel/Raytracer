/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

namespace raytracer {
    Camera::Camera(Math::Vector3D from, Math::Vector3D at, Math::Vector3D vup, double vfov, double ratio, double aperture, double focus)
    {
        double theta = vfov * M_PI / 180;
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = ratio * viewport_height;

        _w = (from - at).unit_vector();
        _u = vup.cross(_w).unit_vector();
        _v = _w.cross(_u);
        _origin = from;
        _horizontal = focus * viewport_width * _u;
        _vertical = focus * viewport_height * _v;
        _lower_left_corner = _origin - _horizontal / 2 - _vertical / 2 - focus * _w;
        _lens_radius = aperture / 2;
    }

    Ray Camera::getRay(double s, double t) const
    {
        Math::Vector3D rd = _lens_radius * Math::Vector3D::random_in_unit_disk();
        Math::Vector3D offset = _u * rd.getX() + _v * rd.getY();
        return Ray(_origin + offset, _lower_left_corner + s * _horizontal + t * _vertical - _origin - offset);
    }
}
