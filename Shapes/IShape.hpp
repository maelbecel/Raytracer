/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** IShape
*/

#ifndef ISHAPE_HPP_
    #define ISHAPE_HPP_

    #include "../Ray.hpp"

    #define UNUSED __attribute__((unused))

    namespace raytracer {
        class IShape {
            public:
                virtual ~IShape() = default;
                virtual bool hits(raytracer::Ray ray) = 0;
                virtual Math::Vector3D getNormal(Math::Point3D point) = 0;
        };
    }

#endif /* !ISHAPE_HPP_ */
