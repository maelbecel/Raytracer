/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** IShape
*/

#ifndef ISHAPE_HPP_
    #define ISHAPE_HPP_

    #include "../Ray.hpp"
    #include "../AABB.hpp"
    #include "../Object/HitRecord.hpp"

    #define UNUSED __attribute__((unused))

    namespace raytracer {
        class IShape {
            public:
                virtual ~IShape() = default;
                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const = 0;
                virtual bool bounding_box(double time0, double time1, raytracer::AABB& output_box) const = 0;
                virtual double densityValue(const Math::Vector3D &o, const Math::Vector3D &v) const = 0;
                virtual Math::Vector3D random(const Math::Vector3D & o) const = 0;
        };
    }

#endif /* !ISHAPE_HPP_ */
