/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
    #define IMATERIAL_HPP_

    #include "../Ray.hpp"
    #include "../Object/HitRecord.hpp"

    namespace raytracer {
        class IMaterial {
            public:
                ~IMaterial() = default ;
                virtual bool scatter(const Ray& r_in, const HitRecord& rec, Math::Color& attenuation, Ray& scattered) const = 0;
                virtual Math::Color emitted(double u, double v, const Math::Vector3D &p) const = 0;

            protected:
            private:
        };
    }

#endif /* !IMATERIAL_HPP_ */
