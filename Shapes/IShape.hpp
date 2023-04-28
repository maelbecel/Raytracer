/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** IShape
*/

#ifndef ISHAPE_HPP_
    #define ISHAPE_HPP_

    #include "../Ray.hpp"
    #include "../Object/HitRecord.hpp"

    #define UNUSED __attribute__((unused))

    namespace raytracer {
        class IShape {
            public:
                virtual ~IShape() = default;
                virtual bool hit(const Ray &r, double min, double max, HitRecord &rec) const = 0;
        };
    }

#endif /* !ISHAPE_HPP_ */
