/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

namespace raytracer {
    /**
     * This function initializes a camera object with given parameters such as
     * position, target, field of view, aspect ratio, aperture, focus distance,
     * and time interval.
     *
     * @param from The position of the camera (where the camera is located in the
     * scene).
     * @param at The "at" parameter is a Math::Vector3D representing the point in
     * 3D space that the camera is pointed towards. It is used to calculate the
     * camera's orientation and direction.
     * @param vup vup is a vector that represents the "up" direction of the
     * camera. It is used to determine the orientation of the camera.
     * @param vfov The vertical field of view in degrees.
     * @param ratio The aspect ratio of the camera's viewport, which is the width
     * of the viewport divided by its height.
     * @param aperture Aperture refers to the size of the opening in the camera
     * lens that allows light to pass through and reach the camera sensor or film.
     * It is measured in f-stops, with a smaller f-stop number indicating a larger
     * aperture and a larger f-stop number indicating a smaller aperture. In this
     * code,
     * @param focus The focus distance of the camera, which determines the
     * distance at which objects will be in focus. This is used in conjunction
     * with the lens aperture to control depth of field in the resulting image.
     * @param t0 t0 is the start time of the camera's exposure. It is used in
     * motion blur calculations when rendering an animation.
     * @param t1 t1 is a double value representing the ending time of the camera's
     * exposure interval. This is used in motion blur effects where the camera
     * captures the movement of objects over a certain time period.
     */
    Camera::Camera(Math::Vector3D from, Math::Vector3D at, Math::Vector3D vup, double vfov, double ratio, double aperture, double focus, double t0, double t1)
    {
        double theta = vfov * M_PI / 180;
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = ratio * viewport_height;

        _ratio = ratio;
        _w = (from - at).unit_vector();
        _u = vup.cross(_w).unit_vector();
        _v = _w.cross(_u);
        _origin = from;
        _horizontal = focus * viewport_width * _u;
        _vertical = focus * viewport_height * _v;
        _lower_left_corner = _origin - _horizontal / 2 - _vertical / 2 - focus * _w;
        _lens_radius = aperture / 2;
        time0 = t0;
        time1 = t1;
        _from = from;
        _direction = Math::Vector3D(at.getX() - from.getX(), at.getY() - from.getY(), at.getZ() - from.getZ());
    }

    /**
     * This function returns a ray from the camera's origin to a point on the
     * image plane based on given parameters.
     *
     * @param s s is a parameter that represents the horizontal position of a
     * pixel on the image plane. It ranges from 0 to 1, where 0 represents the
     * leftmost pixel and 1 represents the rightmost pixel.
     * @param t In the context of ray tracing, `t` typically represents the
     * vertical coordinate of a pixel on the image plane. It is used to calculate
     * the direction of the ray that will be cast from the camera through that
     * pixel.
     *
     * @return A Ray object is being returned.
     */
    Ray Camera::getRay(double s, double t) const
    {
        Math::Vector3D rd = _lens_radius * Math::Vector3D::random_in_unit_disk();
        Math::Vector3D offset = _u * rd.getX() + _v * rd.getY();
        return Ray(_origin + offset, _lower_left_corner + s * _horizontal + t * _vertical - _origin - offset, time0 + (time1 - time0) * random_double());
    }
}
