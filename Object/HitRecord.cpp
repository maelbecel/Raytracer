/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** HitRecord
*/

#include "HitRecord.hpp"

namespace raytracer {
    void HitRecord::setFaceNormal(const Ray &r, const Math::Vector3D &v)
    {
        front_face = r.Direction.dot(v) < 0;
        normal = front_face ? v : -v;
    }

}
