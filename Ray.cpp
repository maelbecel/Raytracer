/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

namespace raytracer {
    Ray::Ray(): Origin(), Direction() {};

    Ray::Ray(Math::Vector3D origin, Math::Vector3D direction, double time): Origin(origin), Direction(direction), tm(time) {}

    Ray::Ray(const Ray &other): Origin(other.Origin), Direction(other.Direction) {}

    /**
     * This is an overloaded assignment operator for the Ray class in C++, which
     * copies the origin and direction of another Ray object.
     *
     * @param other the other Ray
     *
     * @return The `operator=` function is returning a reference to the current
     * object (`*this`).
     */
    Ray &Ray::operator=(const Ray &other) {
        Origin = other.Origin;
        Direction = other.Direction;
        return *this;
    }

    /**
     * This function returns a point on a ray given a distance from its origin.
     *
     * @param x x is a scalar value representing the distance along the direction
     * vector of the ray. The function returns a new vector that is the result of
     * adding x times the direction vector to the origin vector of the ray. This
     * is useful for finding points along the ray at a specific distance from the
     * origin.
     *
     * @return A Math::Vector3D object is being returned. The vector represents a
     * point along the ray, calculated by adding the product of the ray's
     * direction and a scalar value x to the ray's origin.
     */
    Math::Vector3D Ray::at(double x) const { return Origin + x * Direction;};

}
