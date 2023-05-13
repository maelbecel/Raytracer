/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

namespace raytracer {
    /**
     * This is the default constructor for the Ray class in C++, which initializes
     * the Origin and Direction vectors to their default values.
     */
    Ray::Ray(): Origin(), Direction() {};

    /**
     * This is a constructor for a Ray object that takes in an origin, direction,
     * and time.
     *
     * @param origin The origin parameter is a Math::Vector3D object that
     * represents the starting point of the ray. It is the point from which the
     * ray is cast or emitted.
     * @param direction The "direction" parameter in the constructor of the Ray
     * class is a Math::Vector3D object that represents the direction in which the
     * ray is pointing. This vector is used to determine the path that the ray
     * will follow as it travels through space.
     * @param time The "time" parameter in the constructor of the Ray class is a
     * double value that represents the time at which the ray was created or used.
     * This parameter is often used in ray tracing algorithms to simulate motion
     * blur or other time-dependent effects.
     */
    Ray::Ray(Math::Vector3D origin, Math::Vector3D direction, double time): Origin(origin), Direction(direction), tm(time) {}

    /**
     * This is a copy constructor for the Ray class in C++.
     *
     * @param other `other` is a reference to another `Ray` object that is being
     * passed as an argument to the copy constructor of the `Ray` class.
     */
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
