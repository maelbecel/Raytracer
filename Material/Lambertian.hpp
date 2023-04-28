/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
    #define LAMBERTIAN_HPP_

    #include "IMaterial.hpp"

    namespace raytracer {
        class Lambertian : public IMaterial {
            public:
                Lambertian(const Math::Color &color) : albedo(color) {};
                virtual bool scatter(UNUSED const Ray& r_in, const HitRecord& rec, Math::Color& attenuation, Ray& scattered) const override
                {
                    Math::Vector3D scatter_direction = rec.getNormal() + Math::Vector3D::random_unit_vector();
                    if (scatter_direction.near_zero())
                        scatter_direction = rec.getNormal();
                    scattered = Ray(rec.getP(), scatter_direction);
                    attenuation = albedo;
                    return true;
                }

            protected:
            private:
                Math::Color albedo;

        };
    }

#endif /* !LAMBERTIAN_HPP_ */
