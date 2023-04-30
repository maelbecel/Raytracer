/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Isotropic
*/

#ifndef ISOTROPIC_HPP_
    #define ISOTROPIC_HPP_

    #include "IMaterial.hpp"
    #include "../Texture/ITexture.hpp"
    #include "../Texture/SolidColor.hpp"

    namespace raytracer {
        class Isotropic : public IMaterial {
            public:
                Isotropic(Math::Color c) : albedo(std::make_shared<SolidColor>(c)) {}
                Isotropic(std::shared_ptr<ITexture> a) : albedo(a) {}

                virtual bool scatter(const Ray& r_in, const HitRecord& rec, Math::Color& attenuation, Ray& scattered) const override
                {
                    scattered = Ray(rec.getP(), Math::Vector3D::random_in_unit_sphere(), r_in.time());
                    attenuation = albedo->value(rec.u, rec.v, rec.getP());
                    return true;
                }

                virtual Math::Color emitted(UNUSED double u, UNUSED double v, UNUSED const Math::Vector3D &p) const override
                {
                    return Math::Color(0,0,0);
                }

            protected:
            private:
                std::shared_ptr<ITexture> albedo;
        };
    }

#endif /* !ISOTROPIC_HPP_ */
