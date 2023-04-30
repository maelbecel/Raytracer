/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
    #define LAMBERTIAN_HPP_

    #include "IMaterial.hpp"
    #include "../Texture/ITexture.hpp"
    #include "../Texture/SolidColor.hpp"

    namespace raytracer {
        class Lambertian : public IMaterial {
            public:
                Lambertian(const Math::Color &color) : albedo(std::make_shared<SolidColor>(color)) {};
                Lambertian(std::shared_ptr<ITexture> a) : albedo(a) {};

                virtual bool scatter(UNUSED const Ray& r_in, const HitRecord& rec, Math::Color& attenuation, Ray& scattered) const override
                {
                    auto scatter_direction = rec.getNormal() + Math::Vector3D::random_unit_vector();
                    if (scatter_direction.near_zero())
                        scatter_direction = rec.getNormal();
                    scattered = Ray(rec.getP(), scatter_direction, r_in.time());
                    attenuation = albedo->value(rec.u, rec.v, rec.getP());
                    return true;
                }

                virtual Math::Color emitted(UNUSED double u, UNUSED double v, UNUSED const Math::Vector3D &p) const override
                {
                    return Math::Color(0, 0, 0);
                }

            protected:
            private:
                std::shared_ptr<ITexture> albedo;

        };
    }

#endif /* !LAMBERTIAN_HPP_ */
