/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "../Ray.hpp"
    #include "../Maths/Point3D.hpp"
    #include "IShape.hpp"
    #include <iostream>

    namespace raytracer {
        class Sphere : public IShape {
            public:
                Sphere();
                Sphere(Math::Point3D center, double radius);
                Sphere(const Sphere &other);

                ~Sphere() {};

                bool hits(raytracer::Ray ray);
                Math::Vector3D getNormal(Math::Point3D point);

                Math::Point3D Center;
                double Radius;
            protected:
            private:
        };
    }

#endif /* !SPHERE_HPP_ */
