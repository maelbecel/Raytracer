/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** HitRecord
*/

#include "HitRecord.hpp"

namespace raytracer {
    /**
     * The function sets the normal vector and front face flag of a hit record
     * based on the intersection of a ray and a surface.
     *
     * @param r The parameter `r` is a `Ray` object, which represents a ray in 3D
     * space with an origin and a direction.
     * @param v `v` is a `Math::Vector3D` representing the normal vector of the
     * surface at the point of intersection with a ray.
     */
    void HitRecord::setFaceNormal(const Ray &r, const Math::Vector3D &v)
    {
        front_face = r.Direction.dot(v) < 0;
        normal = front_face ? v : -v;
    }

}
