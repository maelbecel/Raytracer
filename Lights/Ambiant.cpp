/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Ambiant
*/

#include "Ambiant.hpp"

namespace raytracer {
    Math::Vector3D Ambiant::getLightVector(Math::Point3D point) const
    {
        return Math::Vector3D(point.X - _point.X, point.Y - _point.Y, point.Z - _point.Z);
    }

    double Ambiant::getLightDistance(Math::Point3D point) const
    {
        return sqrt(pow(point.X - _point.X, 2) + pow(point.Y - _point.Y, 2) + pow(point.Z - _point.Z, 2));
    }

    double Ambiant::getLightIntensity(UNUSED Math::Point3D point) const
    {
        return 1;
    }

    double Ambiant::getLightAngle(Math::Vector3D normal, Math::Point3D point) const
    {
        Math::Vector3D light = getLightVector(point);
        double dot_product = light.X * normal.X + light.Y * normal.Y + light.Z * normal.Z;
        double mag = sqrt(light.X * light.X + light.Y * light.Y + light.Z * light.Z);
        double normal_mag = sqrt(normal.X * normal.X + normal.Y * normal.Y + normal.Z * normal.Z);
        double radians = acos(dot_product / (mag * normal_mag));
        double degrees = radians * (180.0 / M_PI);
        return degrees;
    }
}
