/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Vector3D
*/

#include "Vector3D.hpp"

namespace Math {
    /**
     * The above function overloads the unary minus operator for a 3D vector,
     * returning a new vector with negated components.
     *
     * @return A new instance of the Vector3D class with the negated values of the
     * original instance.
     */
    Vector3D Vector3D::operator-() const
    {
        return Vector3D(-_x, -_y, -_z);
    }

    /**
     * The function overloads the "+=" operator for Vector3D objects to add the
     * components of another Vector3D object to the current object.
     *
     * @return The `operator+=` function is returning a reference to the current
     * object (`*this`).
     */
    Vector3D &Vector3D::operator+=(const Vector3D &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    /**
     * This is a C++ function that subtracts the values of another Vector3D object
     * from the current object and returns a reference to the updated object.
     *
     * @return a reference to the current object, which is of type Vector3D. This
     * is achieved by using the dereference operator (*) on the "this" pointer,
     * which points to the current object.
     */
    Vector3D &Vector3D::operator-=(const Vector3D &other)
    {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    /**
     * This is an implementation of the compound assignment operator for
     * multiplying a Vector3D object by a scalar value.
     *
     * @return a reference to the current object, which is a Vector3D object.
     */
    Vector3D &Vector3D::operator*=(const double &other)
    {
        _x *= other;
        _y *= other;
        _z *= other;
        return *this;
    }

    /**
     * This is an implementation of the division assignment operator for a 3D
     * vector in C++.
     *
     * @return a reference to the current object, which is a Vector3D object.
     */
    Vector3D &Vector3D::operator/=(const double &other)
    {
        _x /= other;
        _y /= other;
        _z /= other;
        return *this;
    }

    /**
     * This function overloads the "+" operator for Vector3D objects to perform
     * vector addition.
     *
     * @param other `other` is a constant reference to another `Vector3D` object
     * that is being added to the current `Vector3D` object using the `+`
     * operator.
     *
     * @return A new Vector3D object that is the result of adding the x, y, and z
     * components of the current Vector3D object and the other Vector3D object.
     */
    Vector3D Vector3D::operator+(const Vector3D &other) const
    {
        return Vector3D(_x + other._x, _y + other._y, _z + other._z);
    }

    /**
     * This is an implementation of the subtraction operator for a 3D vector class
     * in C++.
     *
     * @param other `other` is a constant reference to another `Vector3D` object
     * that is being subtracted from the current `Vector3D` object. The operator
     * overloading function subtracts the corresponding x, y, and z components of
     * the two vectors and returns a new `Vector3D` object
     *
     * @return A new Vector3D object that is the result of subtracting the x, y,
     * and z components of the current Vector3D object from the corresponding
     * components of the other Vector3D object.
     */
    Vector3D Vector3D::operator-(const Vector3D &other) const
    {
        return Vector3D(_x - other._x, _y - other._y, _z - other._z);
    }

    /**
     * This is an overloaded operator function that multiplies a Vector3D object
     * by a scalar value.
     *
     * @param other "other" is a constant reference to a double value that is
     * being used to multiply each component of the Vector3D object.
     *
     * @return A new instance of the Vector3D class is being returned, which is
     * the result of multiplying the current instance's x, y, and z values by the
     * input double value.
     */
    Vector3D Vector3D::operator*(const double &other) const
    {
        return Vector3D(_x * other, _y * other, _z * other);
    }

    /**
     * This is an overloaded operator function for multiplying two Vector3D
     * objects component-wise.
     *
     * @param other The parameter "other" is a constant reference to another
     * Vector3D object that is being multiplied with the current Vector3D object.
     *
     * @return A new Vector3D object that is the result of multiplying the
     * corresponding components of the current Vector3D object and the other
     * Vector3D object.
     */
    Vector3D Vector3D::operator*(const Vector3D &other) const
    {
        return Vector3D(_x * other._x, _y * other._y, _z * other._z);
    }

    /**
     * This is an overloaded division operator for a 3D vector class in C++, which
     * returns a new vector with each component divided by a given scalar value.
     *
     * @param other "other" is a constant double value that is used to divide each
     * component of the Vector3D object by the same value. The resulting Vector3D
     * object will have its x, y, and z components divided by "other".
     *
     * @return A new Vector3D object is being returned, which is the result of
     * dividing each component of the current Vector3D object by the given double
     * value.
     */
    Vector3D Vector3D::operator/(const double &other) const
    {
        return Vector3D(_x / other, _y / other, _z / other);
    }

    /**
     * The function calculates the squared length of a 3D vector.
     *
     * @return The function `len_squared()` is returning the square of the length
     * of a 3D vector represented by the private member variables `_x`, `_y`, and
     * `_z`. The calculation is done by squaring each component of the vector and
     * adding them together. The result is a double value representing the squared
     * length of the vector.
     */
    double Vector3D::len_squared() const
    {
        return _x * _x + _y * _y + _z * _z;
    }

    /**
     * The function returns the length of a 3D vector by taking the square root of
     * the sum of its squared components.
     *
     * @return The function `len()` is returning the length of the 3D vector as a
     * `double` value. It calculates the length by taking the square root of the
     * sum of the squares of the vector's components, which is obtained by calling
     * the `len_squared()` function.
     */
    double Vector3D::len() const
    {
        return sqrt(len_squared());
    }

    /**
     * The function returns a randomly generated 3D vector.
     *
     * @return A random Vector3D object with random x, y, and z values.
     */
    Vector3D Vector3D::random()
    {
        return Vector3D(random_double(), random_double(), random_double());
    }

    /**
     * The function returns a random Vector3D object with x, y, and z values
     * within a given range.
     *
     * @param min The minimum value that can be generated for each component of
     * the random Vector3D.
     * @param max The maximum value that can be generated randomly for each
     * component of the Vector3D.
     *
     * @return A random Vector3D object with x, y, and z values generated using
     * the `random_double_mm` function with the given minimum and maximum values.
     */
    Vector3D Vector3D::random(double min, double max)
    {
        return Vector3D(random_double_mm(min, max), random_double_mm(min, max), random_double_mm(min, max));
    }

    /**
     * The function checks if a 3D vector is near zero within a certain tolerance.
     *
     * @return The function `near_zero()` is returning a boolean value. It returns
     * `true` if the magnitude of all three components of the 3D vector
     * represented by the `Vector3D` object is less than a small threshold value
     * `s` (which is set to `1e-8`), and `false` otherwise.
     */
    bool Vector3D::near_zero() const
    {
        const auto s = 1e-8;
        return (fabs(_x) < s) && (fabs(_y) < s) && (fabs(_z) < s);
    }

    /**
     * The function calculates the dot product of two 3D vectors.
     *
     * @param other The parameter "other" is a constant reference to another
     * Vector3D object, which is being used to calculate the dot product with the
     * current Vector3D object.
     *
     * @return The function `dot` is returning the dot product of the current
     * `Vector3D` object and the `other` `Vector3D` object passed as a parameter.
     */
    double Vector3D::dot(const Vector3D &other) const
    {
        return _x * other._x + _y * other._y + _z * other._z;
    }

    /**
     * The function calculates the cross product of two 3D vectors.
     *
     * @param other The parameter "other" is a constant reference to another
     * Vector3D object that is being used to calculate the cross product with the
     * current Vector3D object.
     *
     * @return A new Vector3D object that is the cross product of the current
     * Vector3D object and the Vector3D object passed as a parameter.
     */
    Vector3D Vector3D::cross(const Vector3D &other) const
    {
        return Vector3D(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
    }

    /**
     * The function returns a unit vector of the current vector.
     *
     * @return A unit vector of the current vector.
     */
    Vector3D Vector3D::unit_vector() const
    {
        return *this / len();
    }

    /**
     * The function generates a random vector within a unit sphere.
     *
     * @return A random vector within a unit sphere centered at the origin is
     * being returned.
     */
    Vector3D Vector3D::random_in_unit_sphere()
    {
        while (true) {
            auto p = Vector3D::random(-1, 1);
            if (p.len_squared() >= 1)
                continue;
            return p;
        }
    }

    /**
     * The function returns a random unit vector by calling the
     * random_in_unit_sphere() function and then normalizing the result.
     *
     * @return A unit vector that is randomly generated within a unit sphere.
     */
    Vector3D Vector3D::random_unit_vector()
    {
        return random_in_unit_sphere().unit_vector();
    }

    /**
     * This function generates a random vector in the hemisphere defined by a
     * given normal vector.
     *
     * @param normal The "normal" parameter is a Vector3D that represents the
     * surface normal of a point on a surface. It is used to determine the
     * hemisphere in which a random point should be generated. The function
     * generates a random point in the hemisphere above the surface defined by the
     * normal vector.
     *
     * @return A random vector in the hemisphere oriented towards the given normal
     * vector. If the randomly generated vector is pointing away from the
     * hemisphere, it is negated and returned.
     */
    Vector3D Vector3D::random_in_hemisphere(const Vector3D &normal)
    {
        Vector3D in_unit_sphere = random_in_unit_sphere();
        if (in_unit_sphere.dot(normal) > 0.0)
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }

    /**
     * The function generates a random 3D vector within a unit disk.
     *
     * @return a random 3D vector that lies within the unit disk (a disk with
     * radius 1 centered at the origin in the xy-plane).
     */
    Vector3D Vector3D::random_in_unit_disk()
    {
        while (true) {
            auto p = Vector3D(random_double_mm(-1, 1), random_double_mm(-1, 1), 0);
            if (p.len_squared() >= 1)
                continue;
            return p;
        }
    }

    /**
     * The function calculates the reflection of a vector off a surface with a
     * given normal vector.
     *
     * @param v The vector representing the incident ray or incoming light
     * direction.
     * @param n The parameter "n" is a Vector3D representing the normal vector of
     * the surface.
     *
     * @return A reflected vector is being returned.
     */
    Vector3D Vector3D::reflect(const Vector3D &v, const Vector3D &n)
    {
        return v - 2 * v.dot(n) * n;
    }

    /**
     * The function calculates the refracted vector of a given incident vector and
     * surface normal with a given ratio of refractive indices.
     *
     * @param uv A unit vector representing the direction of the incident ray.
     * @param n The parameter `n` is a unit vector representing the surface normal
     * at the point of intersection between a ray and a surface.
     * @param etai_over_etat etai_over_etat is the ratio of the refractive indices
     * of the two media that the light is passing through. It is used to calculate
     * the direction of the refracted ray using Snell's law.
     *
     * @return a Vector3D which represents the refracted ray direction.
     */
    Vector3D Vector3D::refract(const Vector3D &uv, const Vector3D &n, double etai_over_etat)
    {
        auto cos_theta = fmin(-uv.dot(n), 1.0);
        Vector3D r_out_perp = etai_over_etat * (uv + cos_theta * n);
        Vector3D r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.len_squared())) * n;
        return r_out_perp + r_out_parallel;
    }

    /**
     * The function normalizes a 3D vector by dividing its components by its
     * magnitude.
     *
     * @return A normalized Vector3D object is being returned.
     */
    Vector3D Vector3D::normalize() const
    {
        double len = sqrt(_x * _x + _y * _y + _z * _z);
        return Vector3D(_x / len, _y / len, _z / len);
    }

    /**
     * The function generates a random vector on the surface of a sphere with a
     * given radius and distance squared.
     *
     * @param radius The radius of the sphere.
     * @param distance_squared The distance_squared parameter is the squared
     * distance from the center of the sphere to the point where the random vector
     * will be generated.
     *
     * @return A randomly generated 3D vector that is uniformly distributed on the
     * surface of a sphere with the given radius and distance squared.
     */
    Vector3D Vector3D::random_to_sphere(double radius, double distance_squared)
    {
        auto r1 = random_double();
        auto r2 = random_double();
        auto z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);
        auto phi = 2 * M_PI * r1;
        auto x = cos(phi) * sqrt(1 - z * z);
        auto y = sin(phi) * sqrt(1 - z * z);
        return Vector3D(x, y, z);
    }

    Vector3D &Vector3D::rotate(double angle)
    {
        double rad = angle * M_PI / 180.0;
        double cs = cos(rad);
        double sn = sin(rad);
        auto x = cs * _x + sn * _z;
        auto z = -sn * _x + cs * _z;
        _x = x;
        _z = z;
        return *this;
    }
}
